#include "function.h"

//���� �д� �Լ�
void fileRead() {
	
	printf("\nEnter the file name you want to assembly (ex >.sic.txt):");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if (fptr == NULL)	// �ҽ��ڵ� ���� �б� �������� ��� ����ó��
	{
		printf("ERROR: Unable to open the %s file.\n", filename);
		exit(1);
	}
}

// ���� ��ŵ�ϱ� (Index�� �ڷ� �ű�)
void SkipSpace() {
	while (Buffer[Index] == ' ' || Buffer[Index] == '\t')
		Index++; // ���� �ε���
}
