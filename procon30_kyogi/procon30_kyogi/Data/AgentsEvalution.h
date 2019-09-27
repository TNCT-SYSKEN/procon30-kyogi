#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//Å‚•]‰¿“_ƒ‹[ƒg
	vector<pair<int, int>> maxRoute;
	float maxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};