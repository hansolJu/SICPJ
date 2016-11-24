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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pass1.h"
#define IMR_SIZE 100
#define MAX_CHAR_SIZE 10
#define INSTRUCTION_SIZE 3


void pass_1(ListHeader *plist, FILE *source) {

	ListHeader *symtab = plist;
	FILE *sourceFile = source;
	Data *linedata;

	unsigned short startingAddr = 0;
	unsigned short LOCCTR = 0;
	unsigned char index = 0;
	int len = 0;
	char *startP, *endP;
	char Buffer[MAX_CHAR_SIZE];

	/* Read first line */
	linedata = readline(sourceFile);

	/* Initialize addr */
	if (strstr(linedata->opcode, "START")) {
		strcpy(plist->name, linedata->label);
		startingAddr = (int)strtol(linedata->operand, NULL, 16);
		LOCCTR = startingAddr;
	}
	linedata = linedata = readline(sourceFile);
	while (!strstr(linedata->opcode, "END") && !feof(sourceFile)) {

		/* 주석 처리 */
		if (!strstr(linedata->label, ".")) {
			/* 레이블이 없는 경우
			if (strstr(linedata->label, "-")) {
			LOCCTR += INSTRUCTION_SIZE;
			continue;
			}
			*/

			/* symbol 중복 검사 */
			if (!strstr(linedata->label, "-") && searchNode(symtab, linedata->label)) {
				setError("Duplicated Symbol");
				printf("\nerror code : %s\n", linedata->label);
			}
			/* SYMTAB 추가 */
			else {
				sprintf(Buffer, "%X", LOCCTR);
				insert_node_last(plist, linedata->label, Buffer, index++);
			}

			/* LOCCTR 증가 */
			if (getValue(linedata->opcode))
				LOCCTR += INSTRUCTION_SIZE;
			else if (strstr(linedata->opcode, "RESW"))
				LOCCTR += atoi(linedata->operand) * INSTRUCTION_SIZE;
			else if (strstr(linedata->opcode, "RESB"))
				LOCCTR += atoi(linedata->operand);
			else if (strstr(linedata->opcode, "WORD")) {
				//modify_Node_Value(symtab, linedata->label, linedata->operand);
				LOCCTR += INSTRUCTION_SIZE;
			}
			else if (strstr(linedata->opcode, "BYTE")) {
				if (startP = strchr(linedata->operand, '\'')) {
					endP = strchr(startP + 1, '\'');
					len = endP - startP - 1;
					endP = strchr(startP, '\'');

					if ((linedata->operand)[0] == 'X')
						LOCCTR += (len + 1) / 2;
					else if ((linedata->operand)[0] == 'C')
						LOCCTR += len;

					//memcpy(linedata->operand, endP + 1, len);
					//(linedata->operand)[len] = '\0';
					//modify_Node_Value(symtab, linedata->label, linedata->operand);
				}
			}
			else {
				setError("Invalid Operator code");
				printf("\nerror code : %s [ %s ] %s\n", linedata->label, linedata->opcode, linedata->operand);
				return;
			}
		}

		/* Read line */
		linedata = linedata = readline(sourceFile);
	}
	/* 프로그램 길이 */
	sprintf(plist->length, "%X", LOCCTR - startingAddr);
	fclose(sourceFile);
}

void pass_another(){
	int LOCCTR[IMR_SIZE];
	printf("Pass 1 Processing...\n");
	while (fgets(Buffer, 256, fptr) != NULL)	// 소스코드 파일에서 코드 읽기
	{
		is_empty_line = strlen(Buffer);

		Index = 0;
		j = 0;
		strcpy(label, ReadLabel());
		if (Label[0] == '.')	// 해당 소스코드가 주석인지 아닌지 확인
			is_comment = 1;
		else
			is_comment = 0;

		if (is_empty_line>1 && is_comment != 1)
		{
			// 인덱스 변수들 초기화
			Index = 0;
			j = 0;

			IMRArray[CSectCounter][ArrayIndex[CSectCounter]] = (IntermediateRec*)malloc(sizeof(IntermediateRec));/* [A] */	// 중간파일 동적할당
			IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LineIndex = ArrayIndex;	// 소스코드 상의 행 삽입
			strcpy(label, ReadLabel());	// 레이블을 읽어 Label에 저장
			strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LabelField, label);	// 레이블을 중간파일에 저장
			SkipSpace();	// 공백 제거

			if (line == start_line)	// 프로그램의 시작 지점이 첫줄이 아닐 경우 (첫번째 줄이 주석일 경우) 예외처리
			{
				strcpy(opcode, ReadOprator());	// Mnemonic 읽기
				strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, opcode); /* [A] */	// 읽은 Mnemonic을 중간파일에 저장
				if (!strcmp(opcode, "START")) {	// 시작주소 초기화
					SkipSpace();
					strcpy(operand, ReadOperand());
					strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, operand);/* [A] */
					LOCCTR[LocctrCounter] = StrToHex(operand);
					start_address[CSectCounter] = LOCCTR[LocctrCounter];
				}
				else {	// 시작 주소가 명시되어있지 않을 경우 0으로 초기화
					LOCCTR[LocctrCounter] = 0;
					start_address[CSectCounter] = LOCCTR[LocctrCounter];
				}
			}
			else {
				strcpy(opcode, ReadOprator());	// OP Code 읽기
				strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, opcode);	// 중간파일에 OP code 복사
				SkipSpace();	// OP code와 피연산자 사이의 공백 제거
				strcpy(operand, ReadOperand());	// 피연산자 부분 읽기
				strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, operand);	// 중간파일에 피연산자 복사

				if (strcmp(opcode, "END"))	// OP code가 END 어셈블러 지시자가 아닐 경우
				{
					if (label[0] != '\0')	// 레이블이 있을 경우
					{
						if (SearchSymtab(label, CSectCounter))	// 같은 이름의 레이블이 있는지 찾음
						{
							// 만약 같은 이름의 레이블이 있을 경우 Alert하고 프로그램 종료
							fclose(fptr);
							printf("ERROR: Duplicate Symbol\n");
							FoundOnSymtab_flag = 0;
							exit(1);
						}
						if (strcmp(opcode, "CSECT")) {	// CSECT가 아닐 경우에만 심볼테이블에 추가
							RecordSymtab(label);	// 같은이름이 없으므로 심볼테이블에 추가
						}
					}

					if (SearchOptab(opcode)) {	// OP Code가 OPTAB에 있을 경우 명령어 형식만큼 메모리 확보
						LOCCTR[LocctrCounter] = loc + (int)(OPTAB[Counter].Format - '0');
						if (ReadFlag(opcode)) {
							// 4형식 명령어일 경우
							LOCCTR[LocctrCounter] += 1;	// 기존에 1바이트 더 추가
						}
					}
					else if (!strcmp(opcode, "WORD")) {	// 3바이트(1 WORD) 확보
						if (isFloatNum(operand)) {
							// 부동소수점은 6바이트 사용하므로
							LOCCTR[LocctrCounter] = loc + 6;
						}
						else {
							LOCCTR[LocctrCounter] = loc + 3;
						}
					}
					else if (!strcmp(opcode, "RESW"))	// 피연산자 갯수의 WORD 만큼 메모리 확보
						LOCCTR[LocctrCounter] = loc + 3 * StrToDec(operand);
					else if (!strcmp(opcode, "RESB"))	// 피연산자 갯수의 바이트만큼 메모리 확보
						LOCCTR[LocctrCounter] = loc + StrToDec(operand);
					else if (!strcmp(opcode, "BYTE")) {	// 1바이트 확보
						if (isFloatNum(operand)) {
							// 부동소수점은 6바이트 사용하므로
							LOCCTR[LocctrCounter] = loc + 6;
						}
						else {
							LOCCTR[LocctrCounter] = loc + ComputeLen(operand);
						}
					}
										
				
						// 각각 END 어셈블러 지시자 추가
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LabelField[0] = '\0';
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->Loc = LOCCTR[LocctrCounter - 1];
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, "END");
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, "");
						program_length[CSectCounter] = LOCCTR[LocctrCounter - 1] - LOCCTR[0];
						ArrayIndex[CSectCounter]++;

						// 새로운 프로그램을 읽기 위한 변수 초기화
						CSectCounter++;
						line = 1;
						loc = 0;
						LocctrCounter = 0;
						LOCCTR[LocctrCounter] = 0;
						FoundOnOptab_flag = 0;	// flag 변수 초기화

												// 새로운 중간파일 생성 및 초기화
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]] = (IntermediateRec *)malloc(sizeof(IntermediateRec));
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LabelField, label);
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, "");
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, opcode);
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LineIndex = 0;
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->Loc = 0;
						RecordSymtab(label);	// 같은이름이 없으므로 심볼테이블에 추가
						start_address[CSectCounter] = LOCCTR[LocctrCounter];
						LocctrCounter++;
						ArrayIndex[CSectCounter]++;
						continue;
					}
					else { // 정의되지 않은 OP code이므로 경고후 프로그램 종료
						fclose(fptr);
						printf("ERROR: Invalid Operation Code[%s]\n", opcode);
						exit(1);
					}
				}
				else {
					// END Assembler Directive를 만났을 경우 피연산자 저장
					strcpy(End_operand, operand);
				}
			}
			loc = LOCCTR[LocctrCounter];	// loc을 다시 설정하고 다음 루프를 준비
			IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->Loc = LOCCTR[LocctrCounter - 1];	// 중간파일에 해당 코드의 메모리 번지 기록
			LocctrCounter++;	// LOCCTR를 접근하는 인덱스 변수 값 증가
			ArrayIndex[CSectCounter]++;	// 다음 코드를 읽기 위한 중간파일의 인덱스 변수 값 증가
		}

		if (is_comment == 1) {	// 첫 줄이 주석일 경우 시작이 되지 않는 오류 수정
			start_line += 1;
		}

		FoundOnOptab_flag = 0;	// flag 변수 초기화
		line += 1;	// 소스 행 1 증가
	}
	program_length[CSectCounter] = LOCCTR[LocctrCounter - 2] - LOCCTR[0];
	// END 지시자를 만났을 경우 END 지시자 바로 이전 소스코드의 메모리 위치와 시작주소를 빼서 총 프로그램 길이 계산

	if (RecordEXTDEFLoc()) {
		printf("ERROR: Isn't exist External Define Label\n");	// EXTDEF 중에 심볼테이블에서 찾을 수 없는 레이블이 있을 경우 예외처리
		fclose(fptr);
		exit(1);
	}

	// Pass 1에서 생성된 심볼테이블 출력
	CreateSymbolTable();

}