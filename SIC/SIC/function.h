#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#define BUFFER_SIZE 256	//����ũ��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//���� ����;
FILE * fptr;
char filename[20];
//���齺ŵ����;
char Buffer[BUFFER_SIZE];
int Index;

//���� �д� �Լ�.
void fileRead();


#define MAX_CHAR_SIZE 10
#define INSTRUCTION_SIZE 3

//����Ʈ �ڷᱸ��
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

// ���� ��ŵ�ϱ� (Index�� �ڷ� �ű�)
void SkipSpace();

#endif