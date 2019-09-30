#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//Å‚•]‰¿“_ƒ‹[ƒg
	vector<pair<int, int>> maxRoute;
	float maxEvalutionPoint;

	vector<pair<int, int>>enemyMaxRoute;
	float enamyMaxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};