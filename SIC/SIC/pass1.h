#ifndef __PASS1_H__
#define __PASS1_H__

#include < stdio.h>
#include <string.h>
#include "function.h"

#define MAX_CHAR_SIZE 10
#define INSTRUCTION_SIZE 3

typedef struct _Data{
	char label[MAX_CHAR_SIZE];
	char opcode[MAX_CHAR_SIZE];
	char operand[MAX_CHAR_SIZE];
	unsigned char is_X_Index;
}Data;

Data *readline(FILE *source) {
	char line[100];
	fgets(line, 100, source);
	line[strlen(line) - 1] = '\0';
	return parse(line);
}


void pass_1(ListHeader *plist, FILE *source);
void SkipSpace();

#endif