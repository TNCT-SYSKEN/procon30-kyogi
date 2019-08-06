#pragma once
#include"ActionManager.h"
class AgentsEvalution {
public:
	//最高評価点ルート
	vector<pair<int, int>> maxRoute;
	int maxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();
private:
	static AgentsEvalution* agentsEvalution;
};