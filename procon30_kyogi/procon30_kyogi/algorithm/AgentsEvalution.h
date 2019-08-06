#pragma once
#include"ActionManager.h"
class AgentsEvalution {
public:
	//Å‚•]‰¿“_ƒ‹[ƒg
	vector<pair<int, int>> maxRoute;
	int maxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();
private:
	static AgentsEvalution* agentsEvalution;
};