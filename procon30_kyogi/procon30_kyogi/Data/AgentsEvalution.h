#pragma once
#include"../algorithm/Action_manager.h"
class AgentsEvalution {
public:
	//�ō��]���_���[�g
	vector<pair<int, int>> maxRoute;
	int maxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* agentsEvalution;
};