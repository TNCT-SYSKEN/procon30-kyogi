#pragma once
#include"../general.h"

class AgentsAction {
public:
	//��Ńf�[�^���c���Ƃ��p�Ɏg��
	int turn;
	//1�Ȃ�move 0�Ȃ�stay
	vector<vector<bool>> actionType;
	//{{number,dx,dy}}
	vector<vector<int>> actionDx;
	vector<vector<int>> actionDy;


	static AgentsAction* getAgentsAction();

private:
	static AgentsAction* agentsAction;

};