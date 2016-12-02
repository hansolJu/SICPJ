#ifndef __PASS1_H__
#define __PASS1_H__
#include "middle.h"

//원시 프로그램 읽기(토크나이져)-->원시문장||오류 플래그
void P1_read_source();

//원시문장-->기호주소할당||명령과 자료주소 할당
void P1_source_statement();

//기호주소 할당-->기호주소
void P1_assign_sym();

//명령과 자료주소 할당
void P1_assign_loc();

//명령과 자료 주소-->기호주소 할당||중간단계 화일의 참조

//기호 주소-->기호표(symtab_) 참조

//오류 플래그




#endif // !__PASS1_H__
