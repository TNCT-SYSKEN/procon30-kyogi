#pragma once
#include"../general.h"

class Agents {
public:
	//{{agentID,x,y},{......}}
	//�����`�[��
	//Agents() : ourAgents() {};



	vector<vector<int>> ourAgents;
	//ourAgents() {};

	//����`�[��
	vector<vector<int>> otherAgents;
	//otherAgents();

	static Agents* getAgents();

private:
	static Agents* AllAgents;

};

//