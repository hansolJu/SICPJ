#include "function.h"

// 공백 스킵하기 (Index를 뒤로 옮김)
void SkipSpace() {
	while (Buffer[Index] == ' ' || Buffer[Index] == '\t')
		Index++;
}
