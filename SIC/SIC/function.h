#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256	// 공백스킵 버퍼의 크기

char Buffer[BUFFER_SIZE];//공백스킵변수;
int Index;

//리스트 자료구조
#define MAX_CHAR_SIZE 10
#define INSTRUCTION_SIZE 3

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

// 공백 스킵하기 (Index를 뒤로 옮김)
void SkipSpace();

#endif