#ifndef __MIDDLE_H__
#define __MIDDLE_H__

#define MAX_CHAR_SIZE 10
#define MAX_OPTAB_SIZE 58

typedef struct _OPTAB {
	char name[7]; //	6 points
	char format[4]; //	up to 3/4
	char code[3]; //	2 points
}optable;

typedef struct _DATA {
	char label[7]; //	6 points
	char opcode[7]; //	up to 3/4
	char operand[9]; //	2 points
	char locctr[7];
}data;


//pass1-->�߰��ܰ� ȭ���� ����-->�߰��ܰ� ȭ��||pass2
void Access_int_file();

//��ȣǥ ����
void Access_symtab();

#endif // !__MIDDLE_H__