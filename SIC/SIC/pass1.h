#ifndef __PASS1_H__
#define __PASS1_H__

#include < stdio.h>
#include <string.h>
#include "function.h"

#define MAX_CHAR_SIZE 10
#define INSTRUCTION_SIZE 3
#define LABEL_LENGTH 24

typedef struct _Data{
	char label[MAX_CHAR_SIZE];
	char opcode[MAX_CHAR_SIZE];
	char operand[MAX_CHAR_SIZE];
	unsigned char is_X_Index;
}Data;

typedef struct IntermediateRecord {	// 중간파일 구조
	unsigned short int LineIndex;	// 소스코드의 행을 저장하는 변수
	unsigned short int Loc;	//  해당 명령어의 메모리상 위치
	unsigned long long int ObjectCode;	//  Pass 2를 거쳐 Assemble된 목적코드
	char LabelField[LABEL_LENGTH];	// 소스코드상 표기되어있는 레이블
	char OperatorField[LABEL_LENGTH];	// 소스코드상 표기되어있는 Mnemonic
	char OperandField[LABEL_LENGTH];	// 소스코드상 표기되어있는 피연산자
}IntermediateRec;

Data *readline(FILE *source) {
	char line[100];
	fgets(line, 100, source);
	line[strlen(line) - 1] = '\0';
	return parse(line);
}


void pass_1(ListHeader *plist, FILE *source);
void SkipSpace();

#endif