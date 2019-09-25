#pragma once
#include"../general.h"

class AgentsAction {
public:
	//後でデータを残すとき用に使う
	int turn;

	//エージェント番号 < 0(turn1) , 1(turn2) , 1(turn3), >
	//1ならmove 0ならstay
	vector<vector<int>> actionType;
	//{{number,{{dx(turn1),dy(turn1)},{dx(turn2),dx(turn2)}...}},..}
	vector<pair<int,vector<pair<int,int>>>> actionDxDy;
	

	static AgentsAction* getAgentsAction();

private:
	static AgentsAction* agentsAction;

};