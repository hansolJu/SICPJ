#include "middle.h"
#include <stdio.h>


//pass||1pass2-->중간단계 화일의 참조-->
void Access_int_file(Node *node) {
	/*
	요구코드(i)
	반환코드(o)
	원시문장(i/o)
	현재위치 계수기 (i/o)
	*/
	Node *OPTAB = node;
	int i = 0;
	char tmp[MAX_CHAR_SIZE];
	char label[MAX_CHAR_SIZE];
	char opcode[MAX_CHAR_SIZE];
	char operand[MAX_CHAR_SIZE];
	/* optab 읽기 */
	FILE *opFile = openFile("optab.txt");

	for (i = 0; i < MAX_OPTAB_SIZE; i++) {
		if (feof(opFile)) break;
		fscanf(opFile, "%s", OPTAB[i].key);
		fscanf(opFile, "%s", OPTAB[i].value);
	}
}


//P1_assign_sym||P2_assemble_inst기호표 참조-->||
void Access_symtab() {
	/*
	요구코드(i)
	반환코드(o)
	기호(i )
	주소(i/o)
	*/
}