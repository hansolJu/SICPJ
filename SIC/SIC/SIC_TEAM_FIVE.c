
//최종 어셈블리프로그램이 동작할려면
// 목적 프로그램의 시작 메모리 주소는 1000번지 => COPY START 1000
//연상 연산 코드를 동등한 기계어로 전환 => OPTAB 이용
//심벌 피연산자를 동등한 기계주소로 전환 => SYMTAB 이용
//기계 명령어를 적당한 형식에 맞추어서 생성 => 직접/인덱스 주소 지정 방식
//원시 프로그램에 나타난 데이타 상수를 기계 내부 표현으로 전환 => 필요한 만큼의 문자(C'...'), 16진수(X'...')상수
//목적 프로그램과 어셈블러 리스트를 작성

/*
sic 기계구조(ADT)짜야함

메모리
크기: 32,768 =2^15 byte

레지스터 :  24비트 5개
	0: A	누산기
	1: X	인덱스
	2: L	연결
	8: PC	프로그램 카운터
	9: SW	상태워드

데이터 형식
	정수 : 24비트 2진수
	음수 : 2의 보수
	문자 : 8bit ASCII코드(오브젝트 코드도 아스키, 16진수 문자로 표현됨)

명령어 형식 :  24BIT

	OPCODE + INDEX REGESITER + ADDRESS
	8			1				15

주소지정 방식


명령어 집합



입력과 출력


*/

//패스 1
/*
*SIC 어셈블러 알고리즘(PASS1)
1. Source file을 라인단위로 읽어들인다.
2. Tokenizer 클래스를 사용하여 일정 스트링을 TOKEN으로 구별
--> LABLE, OPCODE, OPERAND
3. 첫번째 LABLE체크
--> SYMTAB에 레이블을 탐색해서 같은 LABLE이 있으면 오류,
없으면 LABLE이름과 LOC를 저장한다.
4. 두번째 OPCODE체크
--> LOC를 증가시키는데 어셈블리어 지시어(Assembler directive)에 따라
데이터영역의 길이결정과 주소배정에 대한 처리를 한다.
5. 계속 라인단위로 읽어들여서 프로그램 내의 모든 문에 주소를 배정한다.

*SIC 어셈블러 알고리즘(PASS1) 코드화!
public void pass1(string 파일이름){
// 위치카운터(LOCCTR)초기화
try{
//파일열기
//첫번째 라인을 읽어들임
//tokenizer 메소드 통과
Tokenizer.parse(line);
if(분리한 token에서 "START"지시어 찾음){
1.시작주소를 읽어 저장
loc를 셋팅
.
.
}
while(END문이 나올때까지 수행){
if(주석이 아니면)
//레이블 체크
.
.
//opcode체크
.
.
}
//다음라인을 읽어들임
//다시 tokenizer로 토큰으로 구분
}
*/

//패스 2
//1. 명령어를 어셈블 => 연산자 코드를 번역하고(OPTAB), 주소를 조사
//2. BYTE, WORD등으로 정의되는 데이타 값을 생성
//3. 패스 1 동안에 이루어지지 않는 어셈블러 지시자의 처리
//4. 목적 프로그램과 어셈블러 리스트를 출력
/*
SIC어셈블러 알고리즘(PASS2)
public void pass2(String 파일이름){

/ 위치카운터(LOCCTR)초기화.

try{
//파일열기
//첫번째 라인을 읽어들임
//tokenizer 메소드 통과
Tokenizer.parse(line);


if(분리한 token에서 "START"지시어 찾음){
.
.
.
//시작주소를 읽어 저장하고 lc를 셋팅
.
.
}

while(END문이 나올때까지 수행){

if(주석이 아니면){
	if(!Tokenizer.LABLE.equals(".")){
	.
	.
	.
	//OP code를 찾는다.
	( 심벌일때와 "STCH", "LLDCH"일때 각각 Processing되도록 구현)
	.
	.
	.
	}
}
//SYMTAB을 이용하여 object 코드명령어을 어셈블한다.

objCode = OPTAB.getCode(Tokenizer.OPCODE)+
Formatter(Integer.tohexString(opndAddr), 4, 0, 0);
else if{
.
.
.
//어셈블리 지시어(RESW,RESB,BYTE,WORD)등으로 정의되는
DATA값을 생성한다.
.
.
.
}

//List File output print
//END recod 출력
//예외처리( FileNotFoundException, IOException)



*/


//초기화 작업

//OPTAB: 연상 명령어를 찾아서 기계어를 번역하는데 사용
//1. 적어도 명령어 코드와 해당되는 기계 코들를 포함
//2. 명령어 형식과 길이에 대한 정보를 포함하기도 함(서로 다른 명령어를 갖는 기계)
//3. 패스 1에서 원시 프로그램의 명령 코드를 조사하고 확인하는데 사용
//4. 패스 2에서 명령어를 기계어로 번역하는데 사용
//5. 보통 연상 명령어 코드를 키로 갖는 해쉬 테이블로 구성
//6. 내용은 실행 시간에 테이블로 로드되는 것이 아니라, 어셈블러가 작성될때 미리 정의됨
//7. 명령 코드가 추가 또는 삭제될 필요가 없기 때분에 대부분 정적 테이블로 구성

//SYMTAB: 레이블에 배정된 값을 저장하는데 사용
//1. 원시 프로그램의 각 레이블의 이름과 값(주소), 오류 상태(한 기호가 두 장소에서 정의되는 경우)를 나타내기 위한 플래그를 포함
//2. 레이블이 붙여진 데이타 영역이나 명령의 종류, 길이 등에 대한 정보도 포함할 수 있음
//3. 패스 1에서 레이블은 배정되는 주소와 함께 입력
//4. 패스 2에서 피연산자로 사용된 기호는 SYMTAB를 조사하여 어셈블된 명령어에 삽입하기 위한 주소를 찾음
//5. 삽입과 검색의 효율을 위해 보통 해쉬 테이블로 구성

//LOCCTR: 주소 배정을 처리하기 위한 변수 
//1. START문에서 나타낸 시작 주소로 초기화
//2. 각 원시 문장이 나타날 때마다 어셈블된 명령어나 생성된 데이타 영역의 길이가 더해짐
//3. 원시 프로그램에서 레이블을 만날 때 마다 LOCCTR의 현재 값을 레이블의 주소로 배정

//중간화일: 패스 1동안에 수행되어지는 작업을 보존하기 위해 사용
//1. 패스 1은 보통 원시 프로그램과 함께 배정된 주소, 오류 플래그등을 포함하며 패스 2에서 입력으로 사용
//2. OPTAB과 SYMTAB을 가리키는 포인터를 각각 사용되는 연산 코드와 기호에 보존시킴으로써 테이블 탐색의 중복을 피할수 있도록 함

//Sorce DATA
//1. 원시 프로그램은 LABEL, OPCOE와 OPERAND 필드의 고정된 형식으로 작성된다고 가정
//2. 이 필드중의 하나가 수를 표현하는 문자열을 포함하면 접두 문자로 '#'과 함께 그 수의 값을 나타냄 
//3. 모듈 - 기호 테이블의 탐색, 원시 프로그램 읽기


/*
* 한 라인은 분리자로 구분된 토큰에 따라
1개: OPCODE
2개: OPCODE OPERAND
3개: LABEL OPCODE OPERAND
* 피연산자가 ,로 구분된 2개인 경우 붙여 씀 ex) addr r1,r2
*/
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
		fscanf_s(fp, "%s ", table[i].memory, MEMORY_MAX);
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
			token = strtok_s(buffer, "\t\n", &context);  //문자열로 분할하여 토큰에 넣어줌

			strcpy_s(line[lineCount].label, 10, token);  //토큰값에 들어있는걸 line[lineCount].label에 복사함
			token = strtok_s(NULL, "\t\n", &context);    //context에 남은 문자열이 없다면 null을 반환하고 있다면 남은 문자열 토큰에 넣어줌
		}
		else {                                         //원시문 label값이 없고 tab이 있다면
			strcpy_s(line[lineCount].label, 10, "");    //label 값이 없으므로 공백 넣어줌 

			token = strtok_s(buffer, "\t\n", &context); //label값이 없으므로 다음에 나올 memory값을 토큰에 넣어줌
		}

		strcpy_s(line[lineCount].memory, 10, token);   //토큰값에 들어있는걸 line[lineCount].memory에 복사함

		token = strtok_s(NULL, "\t\n", &context);

		strcpy_s(line[lineCount].location, 10, token);  //토큰값에 들어있는걸 line[lineCount].location에 복사함

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

	// 16진수 주소계산을 편하게 하기 위해서 10진수로 변환.
	int hex = atoi(line[0].location);
	int decimal = 0;

	while (hex != 0) {
		decimal += (hex % 10) * radix;

		hex /= 10;
		radix *= 16;
	}

	for (int i = 1; i < lines; i++) {
		strcpy_s(label[labelCount].label, 10, line[i].label);
		label[labelCount].location = decimal;
		printf("%06x %s\n", label[labelCount].location, label[labelCount].label);
		labelCount++;

		decimal += sizeCheck(i);
	}

	return decimal;
}
int sizeCheck(int i) {
	if (strcmp(line[i].memory, "RESW") == 0) {
		return atoi(line[i].location) * WORD_SIZE;
	}
	else if (strcmp(line[i].memory, "BYTE") == 0) {
		int j;
		int flag = 0;
		int count = 0;

		for (j = 0; j < strlen(line[i].location); j++) {
			if (flag) count++;

			if (!flag && line[i].location[j] == '\'') flag = 1;
			else if (line[i].location[j] == '\'') break;
		}

		return count * 1;
	}
	else if (strcmp(line[i].memory, "RESB") == 0) {
		return atoi(line[i].location) * 1;
	}
	else {
		return WORD_SIZE;
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
	int num = 1000 % 10;
	loadTable();

	lines = path1();

	cal(lines);

}
