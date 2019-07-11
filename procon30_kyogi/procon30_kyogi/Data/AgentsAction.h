#pragma once
#include"../general.h"

class AgentsAction {
public:
	//後でデータを残すとき用に使う
	int turn;
	//1ならmove 0ならstay
	vector<vector<bool>> actionType;
	//{{number,dx,dy}}
	vector<vector<int>> actionDx;
	vector<vector<int>> actionDy;


	static AgentsAction* getAgentsAction();

private:
	static AgentsAction* agentsAction;

};