#include "function.h"

// ���� ��ŵ�ϱ� (Index�� �ڷ� �ű�)
void SkipSpace() {
	while (Buffer[Index] == ' ' || Buffer[Index] == '\t')
		Index++;
}
