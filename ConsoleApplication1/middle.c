#include "middle.h"
#include <stdio.h>


//pass||1pass2-->�߰��ܰ� ȭ���� ����-->
void Access_int_file(Node *node) {
	/*
	�䱸�ڵ�(i)
	��ȯ�ڵ�(o)
	���ù���(i/o)
	������ġ ����� (i/o)
	*/
	Node *OPTAB = node;
	int i = 0;
	char tmp[MAX_CHAR_SIZE];
	char label[MAX_CHAR_SIZE];
	char opcode[MAX_CHAR_SIZE];
	char operand[MAX_CHAR_SIZE];
	/* optab �б� */
	FILE *opFile = openFile("optab.txt");

	for (i = 0; i < MAX_OPTAB_SIZE; i++) {
		if (feof(opFile)) break;
		fscanf(opFile, "%s", OPTAB[i].key);
		fscanf(opFile, "%s", OPTAB[i].value);
	}
}


//P1_assign_sym||P2_assemble_inst��ȣǥ ����-->||
void Access_symtab() {
	/*
	�䱸�ڵ�(i)
	��ȯ�ڵ�(o)
	��ȣ(i )
	�ּ�(i/o)
	*/
}