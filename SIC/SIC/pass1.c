#include < stdio.h>
#include <string.h>
#include "pass1.h"
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
	char temp[MAX_CHAR_SIZE];

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

		/* �ּ� ó�� */
		if (!strstr(linedata->label, ".")) {
			/* ���̺��� ���� ���
			if (strstr(linedata->label, "-")) {
			LOCCTR += INSTRUCTION_SIZE;
			continue;
			}
			*/

			/* symbol �ߺ� �˻� */
			if (!strstr(linedata->label, "-") && searchNode(symtab, linedata->label)) {
				setError("Duplicated Symbol");
				printf("\nerror code : %s\n", linedata->label);
			}
			/* SYMTAB �߰� */
			else {
				sprintf(temp, "%X", LOCCTR);
				insert_node_last(plist, linedata->label, temp, index++);
			}

			/* LOCCTR ���� */
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
	/* ���α׷� ���� */
	sprintf(plist->length, "%X", LOCCTR - startingAddr);
	fclose(sourceFile);
}

void pass_another(){
	printf("Pass 1 Processing...\n");
	while (fgets(Buffer, 256, fptr) != NULL)	// �ҽ��ڵ� ���Ͽ��� �ڵ� �б�
	{
		is_empty_line = strlen(Buffer);

		Index = 0;
		j = 0;
		strcpy(label, ReadLabel());
		if (Label[0] == '.')	// �ش� �ҽ��ڵ尡 �ּ����� �ƴ��� Ȯ��
			is_comment = 1;
		else
			is_comment = 0;

		if (is_empty_line>1 && is_comment != 1)
		{
			// �ε��� ������ �ʱ�ȭ
			Index = 0;
			j = 0;

			IMRArray[CSectCounter][ArrayIndex[CSectCounter]] = (IntermediateRec*)malloc(sizeof(IntermediateRec));/* [A] */	// �߰����� �����Ҵ�
			IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LineIndex = ArrayIndex;	// �ҽ��ڵ� ���� �� ����
			strcpy(label, ReadLabel());	// ���̺��� �о� Label�� ����
			strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LabelField, label);	// ���̺��� �߰����Ͽ� ����
			SkipSpace();	// ���� ����

			if (line == start_line)	// ���α׷��� ���� ������ ù���� �ƴ� ��� (ù��° ���� �ּ��� ���) ����ó��
			{
				strcpy(opcode, ReadOprator());	// Mnemonic �б�
				strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, opcode); /* [A] */	// ���� Mnemonic�� �߰����Ͽ� ����
				if (!strcmp(opcode, "START")) {	// �����ּ� �ʱ�ȭ
					SkipSpace();
					strcpy(operand, ReadOperand());
					strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, operand);/* [A] */
					LOCCTR[LocctrCounter] = StrToHex(operand);
					start_address[CSectCounter] = LOCCTR[LocctrCounter];
				}
				else {	// ���� �ּҰ� ��õǾ����� ���� ��� 0���� �ʱ�ȭ
					LOCCTR[LocctrCounter] = 0;
					start_address[CSectCounter] = LOCCTR[LocctrCounter];
				}
			}
			else {
				strcpy(opcode, ReadOprator());	// OP Code �б�
				strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, opcode);	// �߰����Ͽ� OP code ����
				SkipSpace();	// OP code�� �ǿ����� ������ ���� ����
				strcpy(operand, ReadOperand());	// �ǿ����� �κ� �б�
				strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, operand);	// �߰����Ͽ� �ǿ����� ����

				if (strcmp(opcode, "END"))	// OP code�� END ����� �����ڰ� �ƴ� ���
				{
					if (label[0] != '\0')	// ���̺��� ���� ���
					{
						if (SearchSymtab(label, CSectCounter))	// ���� �̸��� ���̺��� �ִ��� ã��
						{
							// ���� ���� �̸��� ���̺��� ���� ��� Alert�ϰ� ���α׷� ����
							fclose(fptr);
							printf("ERROR: Duplicate Symbol\n");
							FoundOnSymtab_flag = 0;
							exit(1);
						}
						if (strcmp(opcode, "CSECT")) {	// CSECT�� �ƴ� ��쿡�� �ɺ����̺� �߰�
							RecordSymtab(label);	// �����̸��� �����Ƿ� �ɺ����̺� �߰�
						}
					}

					if (SearchOptab(opcode)) {	// OP Code�� OPTAB�� ���� ��� ��ɾ� ���ĸ�ŭ �޸� Ȯ��
						LOCCTR[LocctrCounter] = loc + (int)(OPTAB[Counter].Format - '0');
						if (ReadFlag(opcode)) {
							// 4���� ��ɾ��� ���
							LOCCTR[LocctrCounter] += 1;	// ������ 1����Ʈ �� �߰�
						}
					}
					else if (!strcmp(opcode, "WORD")) {	// 3����Ʈ(1 WORD) Ȯ��
						if (isFloatNum(operand)) {
							// �ε��Ҽ����� 6����Ʈ ����ϹǷ�
							LOCCTR[LocctrCounter] = loc + 6;
						}
						else {
							LOCCTR[LocctrCounter] = loc + 3;
						}
					}
					else if (!strcmp(opcode, "RESW"))	// �ǿ����� ������ WORD ��ŭ �޸� Ȯ��
						LOCCTR[LocctrCounter] = loc + 3 * StrToDec(operand);
					else if (!strcmp(opcode, "RESB"))	// �ǿ����� ������ ����Ʈ��ŭ �޸� Ȯ��
						LOCCTR[LocctrCounter] = loc + StrToDec(operand);
					else if (!strcmp(opcode, "BYTE")) {	// 1����Ʈ Ȯ��
						if (isFloatNum(operand)) {
							// �ε��Ҽ����� 6����Ʈ ����ϹǷ�
							LOCCTR[LocctrCounter] = loc + 6;
						}
						else {
							LOCCTR[LocctrCounter] = loc + ComputeLen(operand);
						}
					}
					else if (!strcmp(opcode, "BASE")
						|| !strcmp(opcode, "NOBASE")) {
						// ���޸� ó���� �ʿ��� Assembler Directive�� �ƴ� ��� Loc�� ����
						LOCCTR[LocctrCounter] = loc;
					}
					else if (!strcmp(opcode, "EXTDEF")
						|| !strcmp(opcode, "EXTREF")) {
						// �ܺ� ����, ���� ���̺��� ��� , ������ ���̺� �߰�
						i = 0; tempLabelIdx = 0;
						while (1) {
							if (operand[i] == ',' || operand[i] == '\0') {
								// , Ȥ�� \0�� ���� ��� ���
								tempLabel[tempLabelIdx] = '\0';
								// ���� �ٸ� ���̺� ���
								if (!strcmp(opcode, "EXTDEF")) {
									RecordEXTDEF(tempLabel);
								}
								else if (!strcmp(opcode, "EXTREF")) {
									RecordEXTREF(tempLabel);
								}
								tempLabelIdx = 0;
								if (operand[i] == '\0') break;	// \0�� ������ ��� break;
							}
							else {
								tempLabel[tempLabelIdx++] = operand[i];
							}
							i++;
						}
						LOCCTR[LocctrCounter] = loc;
					}
					else if (!strcmp(opcode, "CSECT")) {
						// ������ �ۼ��� �ɺ����̺��� ������� �ܺ� ���� ���̺��� ��ġ�� ���
						if (RecordEXTDEFLoc()) {
							printf("ERROR: Isn't exist External Define Label\n");	// EXTDEF �߿� �ɺ����̺��� ã�� �� ���� ���̺��� ���� ��� ����ó��
							fclose(fptr);
							exit(1);
						}

						// ���� END ����� ������ �߰�
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LabelField[0] = '\0';
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->Loc = LOCCTR[LocctrCounter - 1];
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, "END");
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, "");
						program_length[CSectCounter] = LOCCTR[LocctrCounter - 1] - LOCCTR[0];
						ArrayIndex[CSectCounter]++;

						// ���ο� ���α׷��� �б� ���� ���� �ʱ�ȭ
						CSectCounter++;
						line = 1;
						loc = 0;
						LocctrCounter = 0;
						LOCCTR[LocctrCounter] = 0;
						FoundOnOptab_flag = 0;	// flag ���� �ʱ�ȭ

												// ���ο� �߰����� ���� �� �ʱ�ȭ
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]] = (IntermediateRec *)malloc(sizeof(IntermediateRec));
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LabelField, label);
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperandField, "");
						strcpy(IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->OperatorField, opcode);
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->LineIndex = 0;
						IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->Loc = 0;
						RecordSymtab(label);	// �����̸��� �����Ƿ� �ɺ����̺� �߰�
						start_address[CSectCounter] = LOCCTR[LocctrCounter];
						LocctrCounter++;
						ArrayIndex[CSectCounter]++;
						continue;
					}
					else { // ���ǵ��� ���� OP code�̹Ƿ� ����� ���α׷� ����
						fclose(fptr);
						printf("ERROR: Invalid Operation Code[%s]\n", opcode);
						exit(1);
					}
				}
				else {
					// END Assembler Directive�� ������ ��� �ǿ����� ����
					strcpy(End_operand, operand);
				}
			}
			loc = LOCCTR[LocctrCounter];	// loc�� �ٽ� �����ϰ� ���� ������ �غ�
			IMRArray[CSectCounter][ArrayIndex[CSectCounter]]->Loc = LOCCTR[LocctrCounter - 1];	// �߰����Ͽ� �ش� �ڵ��� �޸� ���� ���
			LocctrCounter++;	// LOCCTR�� �����ϴ� �ε��� ���� �� ����
			ArrayIndex[CSectCounter]++;	// ���� �ڵ带 �б� ���� �߰������� �ε��� ���� �� ����
		}

		if (is_comment == 1) {	// ù ���� �ּ��� ��� ������ ���� �ʴ� ���� ����
			start_line += 1;
		}

		FoundOnOptab_flag = 0;	// flag ���� �ʱ�ȭ
		line += 1;	// �ҽ� �� 1 ����
	}
	program_length[CSectCounter] = LOCCTR[LocctrCounter - 2] - LOCCTR[0];
	// END �����ڸ� ������ ��� END ������ �ٷ� ���� �ҽ��ڵ��� �޸� ��ġ�� �����ּҸ� ���� �� ���α׷� ���� ���

	if (RecordEXTDEFLoc()) {
		printf("ERROR: Isn't exist External Define Label\n");	// EXTDEF �߿� �ɺ����̺��� ã�� �� ���� ���̺��� ���� ��� ����ó��
		fclose(fptr);
		exit(1);
	}

	// Pass 1���� ������ �ɺ����̺� ���
	CreateSymbolTable();

}