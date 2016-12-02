#include "middle.h"
#include "pass1.h"
#include<stdio.h>

void Pass_1() {
	/*
	시작
	첫번째줄을 읽는다
	if opcode = 'start'{
		#[operand]를 시작 주소로 저장
		loc를 시작 주소로 초기화
		중간화일에 이줄을 write한다.
		다음줄을 읽는다.
	else
		loc을 0으로 초기화한다.
	}
	while(opcode = 'end')
	{
		if(이 줄이 주석이 아니라면)
			if(LABEL 필드안에 심볼이 있다면){
				//LABEL을 SYMTAB에서 찾는다.
				if(SYMTAB 에 LABEL이있다면)
					ERROR("SYMBOL중복")
				else
					insert(lable, locctr)을 SYMTAB에 삽입

		
	*/
	

	}


//원시 프로그램 읽기(토크나이져)-->(각 원시문장 마다) || 오류 플래그
void P1_read_source(FILE *source) {
	/*
	반환코드(o)(r_code)
	원시문장(i/o)
	오류 플래그(i/o)

	*/

}

//명령과 자료주소 할당(주석문이 아닌 각 문장마다)
void P1_assign_loc() {

	/*
	원시문장(i)
	오류 플래그(o)
	현재 위치 계수기(i)
	다음 위치 계수기(o)

	*/

}

//기호주소 할당-->기호주소(주석문이 아닌 각 문장마다)
void P1_assign_sym() {

	/*
	원시문장(i)
	오류 플래그(o)
	현재 위치 계수기(i)

	*/

	//Access_int_file(각원시 문장마다)

	//명령과 자료 주소-->기호주소 할당||중간단계 화일의 참조

	//기호 주소-->기호표(symtab_) 참조

	//오류 플래그
