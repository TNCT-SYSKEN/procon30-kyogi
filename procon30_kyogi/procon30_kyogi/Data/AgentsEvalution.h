#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//最高評価点ルート
	vector<pair<int, int>> maxRoute;
	float maxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};