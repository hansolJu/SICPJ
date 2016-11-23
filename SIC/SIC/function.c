#include "function.h"

//파일 읽는 함수
void fileRead() {
	
	printf("\nEnter the file name you want to assembly (ex >.sic.txt):");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if (fptr == NULL)	// 소스코드 파일 읽기 실패했을 경우 예외처리
	{
		printf("ERROR: Unable to open the %s file.\n", filename);
		exit(1);
	}
}

// 공백 스킵하기 (Index를 뒤로 옮김)
void SkipSpace() {
	while (Buffer[Index] == ' ' || Buffer[Index] == '\t')
		Index++; // 버퍼 인덱스
}

char strtok() {
	inFile = fopen("./opcode.s", "r");
	opcFile = fopen("./opcode", "r");
	int i = 0;
	int j = 0;
	//<<----------------------------------input.txt open--------------------------------->>

	memset(intab, 0, sizeof(intab));
	char inTemp[255] = "\0";
	char *inLine;
	char *inToken;
	char inSeps[] = "\n\t";
	intab[0].length = 0;
	if (inFile != NULL) {									
		while (!feof(inFile)) {						//inFile의 끝까지
			inLine = fgets(inTemp, sizeof(inTemp), inFile);		// 한 줄씩 읽어들이기
			i = 0;
			inToken = strtok(inLine, inSeps);
			while (inToken != NULL) {				//inToken이 Not NULL때 까지
				if (i == 0) {
					strcpy(intab[intab[0].length].lable, inToken);	//i가 0일 때 inToken을 intab의 문자열을 label에 넣는다.
				}
				else if (i == 1) {
					strcpy(intab[intab[0].length].inst, inToken);   //label을 넣은 후 i++ 후에 다음 Token을 intab의 inst에 넣는다.
				}
				else {
					strcpy(intab[intab[0].length].symbol, inToken);  //나머지 Token을 intab의 symbol에 저장.
				}
				i++;
				inToken = strtok(NULL, inSeps);
			}
			intab[0].length++;
		}
		/*
		for(j=0; j<intab[0].length-1; j++)
		printf("[%s] [%s] [%s]\n",intab[j].lable, intab[j].inst, intab[j].symbol);
		*/
	}
	else {
		printf("no file !!");
	}

	//<<----------------------------------opcode.txt open--------------------------------->>

	memset(opctab, 0, sizeof(opctab));
	char opcTemp[255] = "\0";
	char *opcLine;
	char *opcToken;
	char opcSeps[] = "\n\t";
	opctab[0].length = 0;

	if (opcFile != NULL) {
		while (!feof(opcFile)) {
			opcLine = fgets(opcTemp, sizeof(opcTemp), opcFile);
			i = 0;
			opcToken = strtok(opcLine, opcSeps);
			while (opcToken != NULL) {
				if (i == 0) {
					strcpy(opctab[opctab[0].length].inst, opcToken);	//첫 번째 등장하는 Token을 inst에 저장.
				}
				else {
					strcpy(opctab[opctab[0].length].code, opcToken);	//두 번째 등장하는 Token을 code에 저장
				}
				i++;
				opcToken = strtok(NULL, opcSeps);
			}
			opctab[0].length++;
		}
		/*
		for(j=0; j<opctab[0].length-1; j++)
		printf("[%s] [%s]\n", opctab[j].inst, opctab[j].code);
		*/
	}
	else {
		printf("no file !!");
	}

	//file close
	fclose(inFile);
	fclose(opcFile);
}