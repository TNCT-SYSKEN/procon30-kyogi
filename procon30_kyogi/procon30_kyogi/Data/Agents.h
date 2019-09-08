#pragma once
#include"../general.h"

class Agents{
public:
	//{{agentID,x,y},{......}}
	//自分チーム
	//自分のチームエージェントの数
	int agentsnum;

	vector<vector<int>> ourAgents;
	//相手チーム
	vector<vector<int>> otherAgents;
	
	
	static Agents* getAgents();

private:
	static Agents* AllAgents;
	
};