#pragma once
#include"../general.h"

class Agents{
public:
	//{{agentID,x,y},{......}}
	//�����`�[��
	//Agents() : ourAgents() {};

	
	
	vector<vector<int>> ourAgents;
	//ourAgents() {};

	//error
	//Agents() : otherAgents() {};
	//����`�[��
	vector<vector<int>> otherAgents;
	//otherAgents();
	
	static Agents* getAgents();

private:
	static Agents* AllAgents;
	
};

//