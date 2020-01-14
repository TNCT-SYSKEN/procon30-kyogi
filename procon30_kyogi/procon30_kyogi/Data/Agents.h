#pragma once
#include"../general.h"

class Agents {
public:
	//{{agentID,x,y},{......}}
	//自分チーム
	//Agents() : ourAgents() {};



	vector<vector<int>> ourAgents;
	//ourAgents() {};

	//相手チーム
	vector<vector<int>> otherAgents;
	//otherAgents();

	static Agents* getAgents();

private:
	static Agents* AllAgents;

};

//