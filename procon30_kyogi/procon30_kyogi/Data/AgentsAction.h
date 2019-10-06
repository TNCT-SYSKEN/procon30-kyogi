#pragma once
#include"../general.h"

class AgentsAction {
public:
	//��Ńf�[�^���c���Ƃ��p�Ɏg��
	int turn;

	//�G�[�W�F���g�ԍ� < 0(turn1) , 1(turn2) , 1(turn3), >
	//1�Ȃ�move 0�Ȃ�stay
	vector<vector<int>> actionType;


	
	//{{number,{{dx(turn1),dy(turn1)},{dx(turn2),dx(turn2)}...}},..}
	//�G�[�W�F���g�̐�(��ǂ݃^�[���iagentNuber(dx,dy)�j)
	vector<vector<pair<int,pair<int,int>>>>actionDxDy;
	
	vector<pair<int, pair<int, int>>>actionEnemyDxDy;

	static AgentsAction* getAgentsAction();

private:
	static AgentsAction* agentsAction;

};