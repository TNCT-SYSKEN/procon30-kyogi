#pragma once
#include"../general.h"

class Agents{
public:
	//{{agentID,x,y},{......}}
	//�����`�[��
	vector<vector<int>> ourAgents;
	//����`�[��
	vector<vector<int>> otherAgents;
	
	
	static Agents* getAgents();

private:
	static Agents* AllAgents;
	
};