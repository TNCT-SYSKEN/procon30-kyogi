#pragma once
#include"../general.h"

class Agents{
public:
	//{{agentID,x,y},{......}}
	//�����`�[��
	//�����̃`�[���G�[�W�F���g�̐�
	int agentsnum;

	vector<vector<int>> ourAgents;
	//����`�[��
	vector<vector<int>> otherAgents;
	
	
	static Agents* getAgents();

private:
	static Agents* AllAgents;
	
};