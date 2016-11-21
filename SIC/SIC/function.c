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
