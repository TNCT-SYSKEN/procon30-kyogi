#include "Action_manager.h"//general.h, Field_test.h, Hyouka.h

//���̃t�@�C�������s���邱�Ƃł��ׂẴA���S���Y�����������s������
//master�I�ȃt�@�C��


//	1.�]���v�Z
//	2.�ړ�����\��


int Action_manager::Action(int)
{	
	Field_test FT;
	//Hyouka.cpp�̊֐����Ăяo��
	//���݂̓��_�Ȃǂ������ƕʂ̃t�@�C���A�������͊֐��Ŏ擾����K�v������B


	Hyouka Hy;
	Action_manager Ac_m;

	Ac_m.Now_Optim = Hy.hyouka_keisan(FT.points, FT.tiled, FT.agents, FT.my_team_point, FT.other_team_point);






	return 0;
}
