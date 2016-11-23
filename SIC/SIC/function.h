#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#define BUFFER_SIZE 256	//버퍼크기
#define MAX 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//파일 변수;

FILE *inFile;	//opcode.s
FILE *opcFile;	//opcode
FILE * fptr;
char filename[20];
//공백스킵변수;
char Buffer[BUFFER_SIZE];
int Index;

//파일 읽는 함수.
void fileRead();


#define MAX_CHAR_SIZE 10
#define INSTRUCTION_SIZE 3

//리스트 자료구조
typedef struct {
	char key[MAX_CHAR_SIZE];
	char value[MAX_CHAR_SIZE];
}Node;

typedef struct _ListNode {
	Node node;
	struct ListNode *link;
}ListNode;

typedef struct _ListHeader {
	char name[MAX_CHAR_SIZE];
	char length[MAX_CHAR_SIZE];
	ListNode *head;
	ListNode *tail;
}ListHeader;
//


typedef struct {
	char lable[7];
	char inst[7];
	char symbol[7];
	int length;
}INPUT;

typedef struct {
	char inst[7];
	char code[7];
	int length;
}OPCODE;

INPUT intab[MAX];
OPCODE opctab[MAX];


// 공백 스킵하기 (Index를 뒤로 옮김)
void SkipSpace();

#endif