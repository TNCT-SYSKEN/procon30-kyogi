#pragma once
#include"ActionManager.h"
class AgentsEvalution {
public:
	//�ō��]���_���[�g
	vector<pair<int, int>> maxRoute;
	int maxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();
private:
	static AgentsEvalution* agentsEvalution;
};