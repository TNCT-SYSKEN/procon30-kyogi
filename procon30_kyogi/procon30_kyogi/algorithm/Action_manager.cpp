#include "Action_manager.h"//general.h, Field_test.h, Hyouka.h

//���̃t�@�C�������s���邱�Ƃł��ׂẴA���S���Y�����������s������
//master�I�ȃt�@�C��


//	1.�]���v�Z
//	2.�ړ�����\��


void Action_manager::Action()
{	

	//Hyouka.cpp�̊֐����Ăяo��
	//���݂̓��_�Ȃǂ������ƕʂ̃t�@�C���A�������͊֐��Ŏ擾����K�v������B


	Prefetching prefetching;

	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();

	Judge judge;
	
	Map* map;
	map = map->getMap();

	//�S�T�����[�h�łȂ�������
	if (!map->isSearchAll) {
		prefetching.hyoukaKeisan();
	}
	else {
		judge.fullSearch();
	}

}
