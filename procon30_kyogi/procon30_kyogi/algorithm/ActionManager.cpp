#include "ActionManager.h"//general.h, Field_test.h, Hyouka.h
#include "Prefetching.cpp"
//���̃t�@�C�������s���邱�Ƃł��ׂẴA���S���Y�����������s������
//master�I�ȃt�@�C��


//	1.�]���v�Z
//	2.�ړ�����\��


void ActionManager::Action(int)
{	
	//�e�X�g�p�̒�`�i��ŏ����j
	Field_test fieldtest;
	fieldtest.fieldTest();

	//�]���v�Z
	Prefetching prefetching;
	prefetching.hyoukaKeisan();
	//Hyouka hyouka;
	//hyouka.hyoukaKeisan();
	

}
