#pragma once
#include"../general.h"

class AgentsAction {
public:
	//後でデータを残すとき用に使う
	int turn;

	//エージェント番号 < 0(turn1) , 1(turn2) , 1(turn3), >
	//1ならmove 0ならstay -1ならremove
	vector<vector<int>> actionType;



	//{{number,{{dx(turn1),dy(turn1)},{dx(turn2),dx(turn2)}...}},..}
	//エージェントの数(先読みターン（agentNumber(dx,dy)）)
	vector<vector<pair<int, pair<int, int>>>>actionDxDy;

	//turn0でアクセスさせないようにする
	vector<pair<int, pair<int, int>>>actionEnemyDxDy;

	static AgentsAction* getAgentsAction();

private:
	static AgentsAction* agentsAction;

};