#ifndef __PASS1_H__
#define __PASS1_H__
#include "middle.h"

//���� ���α׷� �б�(��ũ������)-->���ù���||���� �÷���
void P1_read_source();

//���ù���-->��ȣ�ּ��Ҵ�||��ɰ� �ڷ��ּ� �Ҵ�
void P1_source_statement();

//��ȣ�ּ� �Ҵ�-->��ȣ�ּ�
void P1_assign_sym();

//��ɰ� �ڷ��ּ� �Ҵ�
void P1_assign_loc();

//��ɰ� �ڷ� �ּ�-->��ȣ�ּ� �Ҵ�||�߰��ܰ� ȭ���� ����

//��ȣ �ּ�-->��ȣǥ(symtab_) ����

//���� �÷���




#endif // !__PASS1_H__
