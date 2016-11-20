#include <stdio.h>
#include <stdlib.h> //exit()
#include <string.h> //strlen()
#include <ctype.h> //isdigit()
#include <math.h> //pow()

#define SYMMAX 100
#define MAX 100
#define OPCODE_MAX 4
#define MEMORY_MAX 7
#define WORD_SIZE 3
int locctr;  //위치 계수기
int progleng; //전체 프로그램의 길이
struct oneline { //소스 프로그램의 한 라인은 고정된 필드로 구성
	char loc[10]; //기계 주소, 중간코드에서 사용
	char label[10];
	char opcode[10];
	char operand[10];
};

struct operators {
	char name[10];
	char code[9];
};

/*struct operators instruction[26] = { //OPTAB
	{ "ADD", "18" },{ "AND", "40" },{ "COMP", "28" },{ "DIV", "24" },
	{ "J", "3C" },{ "JEQ", "30" },{ "JGT", "34" },{ "JLT", "38" },
	{ "JSUB", "48" },{ "LDA", "00" },{ "LDCH", "50" },{ "LDL", "08" },
	{ "LDX", "04" },{ "MUL", "20" },{ "OR", "44" },{ "RD", "D8" },
	{ "RSUB", "4C" },{ "STA", "0C" },{ "STCH", "54" },{ "STL", "14" },
	{ "STSW", "E8" },{ "STX", "10" },{ "SUB", "1C" },{ "TD", "E0" },
	{ "TIX", "2C" },{ "WD", "DC" }
};*/

typedef struct TABLE {
	char opcode[OPCODE_MAX];      //OPTAB 연산명령
	char memory[MEMORY_MAX];      //OPTAB 연산코드
}TABLE;

typedef struct LINE {
	char label[MAX];              //원시문 COPY, FIRST....등등 넣어주는 배열
	char memory[MEMORY_MAX];      //원시문 START, STL....등등 넣어주는 배열
	char location[MAX];           //원시문 1000, RETADR...등등 넣어주는 배열   
}LINE;

typedef struct LABEL {
	char label[MAX];              //원시문 lable 값을 옮겨주기 위해 선언
	int location;                 //원시문 location 값
}LABEL;

TABLE table[MAX];
LINE line[MAX];
LABEL label[MAX];

struct entry {
	char name[10]; //레이블의 이름
	int value;  //레이블에 배정된 값
	int errorflag; //한 기호가 두 장소에서 정의되는 오류를 나타내는 플래그, error: set
};
struct entry symtable[SYMMAX]; //심벌 테이블 배열

int lastentry = 0; //symtable에서 새로운 라벨이 들어갈 배열 첨자 위치

void loadTable() {           //파일에 저장된 OPTAB 열기 
	FILE* fp;
	int i = 0;

     fopen_s(&fp, "optable", "r");

	while (!feof(fp)) {
		fscanf_s(fp, "%s ", table[i].memory,MEMORY_MAX);
		fscanf_s(fp, "%s", table[i].opcode, OPCODE_MAX);
		i++;
	}

	fclose(fp);
}
//void path1();
int path1() {
	FILE* fp;
	char buffer[MAX];       //파일 opcode에 저장된 어셈블 소스를 버퍼 배열에 옮김
	char* token;           
	int lineCount = 0;      //선언하므로써 어셈블 소스의 총길이를 알 수 있음
	char* context = NULL;   //strtok_s 사용하기 위해 선언 strtok 사용하면 필요 없음, 버퍼에 남은 문자열
	fopen_s(&fp, "opcode.s", "r");     //저장된 어셈블 소스 열기
	while (fgets(buffer, MAX, fp) != NULL) {

		if (buffer[0] != '\t') {                        //opcode에 저장된 이섬블 소스 tab으로 구분, label값이 tab이 아니라면
			token = strtok_s(buffer, "\t\n",&context);  //문자열로 분할하여 토큰에 넣어줌
			
			strcpy_s(line[lineCount].label, 10,token);  //토큰값에 들어있는걸 line[lineCount].label에 복사함
			token = strtok_s(NULL, "\t\n",&context);    //context에 남은 문자열이 없다면 null을 반환하고 있다면 남은 문자열 토큰에 넣어줌
		}
		else {                                         //원시문 label값이 없고 tab이 있다면
			strcpy_s(line[lineCount].label,10, "");    //label 값이 없으므로 공백 넣어줌 

			token = strtok_s(buffer, "\t\n",&context); //label값이 없으므로 다음에 나올 memory값을 토큰에 넣어줌
		}

		strcpy_s(line[lineCount].memory,10, token);   //토큰값에 들어있는걸 line[lineCount].memory에 복사함

		token = strtok_s(NULL, "\t\n",&context);

		strcpy_s(line[lineCount].location,10, token);  //토큰값에 들어있는걸 line[lineCount].location에 복사함

		printf("%s %s %s\n", line[lineCount].label, line[lineCount].memory, line[lineCount].location);

		lineCount++;
	}
	printf("\n");
	fclose(fp);

	return lineCount;
}
int cal(lines) {            //원시문 location값
	int i;
	int startLocation = 0;
	int radix = 1;
	int labelCount = 0;
	int hex = atoi(line[0].location);
	int decimal = 0;

	while (hex != 0) {                   // 16진수 주소계산을 편하게 하기 위해서 10진수로 변환.
		decimal += (hex % 10) * radix;
		hex /= 10;
		radix *= 16;
	}
	
	for (int i = 1; i < lines; i++) {
			strcpy_s(label[labelCount].label,10, line[i].label);  //line[i].label에 있는 값을 label[labelCount].label 옮김
			label[labelCount].location = decimal;                 //원시문 location 값에 위에서 변환한 10진수 삽입(처음 시작주소)
			printf("%06x %s\n", label[labelCount].location, label[labelCount].label);
			labelCount++;
		
		decimal += sizeCheck(i);                                  //location 값 증가시키기 위해 sizeCheck함수 호출
	}

	return decimal;
}
int sizeCheck(int i) {
	if (strcmp(line[i].memory, "RESW") == 0) {                   //원시문 메모리값이 RESW이면 RESW의 값만큼 WORD_SIZE 곱해줌
		return atoi(line[i].location) * WORD_SIZE;
	}
	else if (strcmp(line[i].memory, "BYTE") == 0) {              //원시문 메모리값이 BYTE이면
		int j;
		int flag = 0;
		int count = 0;

		for (j = 0; j < strlen(line[i].location); j++) {          //원시문 location길이만큼 포문을 돔
			if (flag)                                             //로케이션 값이 문자면 count 증가
				count++;
			if (!flag && line[i].location[j] == '\'')             //로케이션 값에 '가 나오면 flag 증가
				flag = 1;
			//else if (line[i].location[j] == '\'') 
				//break;
		}
		return count;
	}
	else if (strcmp(line[i].memory, "RESB") == 0) {              //원시문 메모리값이 RESB이면 RESB값만큼 리턴
		return atoi(line[i].location) ;
	}
	else {
		return WORD_SIZE;                                        //위에 경우가 전부 아니면 WORD_SIZE만 증가
	}
}
void path2();
struct oneline readline(FILE *, int);
int lookup(char *);
void insert(char *, int);
int srchop(char *); //OPCODE를 위해 OPTAB를 검색, 리턴값: 검색된 OP의 배열의 첨자 + 1, 실패시 0
int xtoi(char *);
int srchoperand(char *s);
char * file1[20];
char * file2[20];
int main() {
	int lines;
	int num=1000%10;
	loadTable();
	
	lines = path1();

	cal(lines);
	
}
//ㅎㅎ 난똥이야!
// ㅎㅎ 난 똥이다!