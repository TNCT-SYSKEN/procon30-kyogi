#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//�ō��]���_���[�g
	vector<pair<int, int>> maxRoute;
	float maxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};