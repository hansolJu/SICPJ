#include "middle.h"
#include "pass1.h"
#include<stdio.h>

void Pass_1() {
	/*
	����
	ù��°���� �д´�
	if opcode = 'start'{
		#[operand]�� ���� �ּҷ� ����
		loc�� ���� �ּҷ� �ʱ�ȭ
		�߰�ȭ�Ͽ� ������ write�Ѵ�.
		�������� �д´�.
	else
		loc�� 0���� �ʱ�ȭ�Ѵ�.
	}
	while(opcode = 'end')
	{
		if(�� ���� �ּ��� �ƴ϶��)
			if(LABEL �ʵ�ȿ� �ɺ��� �ִٸ�){
				//LABEL�� SYMTAB���� ã�´�.
				if(SYMTAB �� LABEL���ִٸ�)
					ERROR("SYMBOL�ߺ�")
				else
					insert(lable, locctr)�� SYMTAB�� ����

		
	*/
	

	}


//���� ���α׷� �б�(��ũ������)-->(�� ���ù��� ����) || ���� �÷���
void P1_read_source(FILE *source) {
	/*
	��ȯ�ڵ�(o)(r_code)
	���ù���(i/o)
	���� �÷���(i/o)

	*/

}

//��ɰ� �ڷ��ּ� �Ҵ�(�ּ����� �ƴ� �� ���帶��)
void P1_assign_loc() {

	/*
	���ù���(i)
	���� �÷���(o)
	���� ��ġ �����(i)
	���� ��ġ �����(o)

	*/

}

//��ȣ�ּ� �Ҵ�-->��ȣ�ּ�(�ּ����� �ƴ� �� ���帶��)
void P1_assign_sym() {

	/*
	���ù���(i)
	���� �÷���(o)
	���� ��ġ �����(i)

	*/

	//Access_int_file(������ ���帶��)

	//��ɰ� �ڷ� �ּ�-->��ȣ�ּ� �Ҵ�||�߰��ܰ� ȭ���� ����

	//��ȣ �ּ�-->��ȣǥ(symtab_) ����

	//���� �÷���
