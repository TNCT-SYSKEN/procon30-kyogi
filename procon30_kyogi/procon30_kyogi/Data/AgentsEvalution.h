#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//�ō��]���_���[�g
	vector<pair<int, int>> maxRoute;
	float maxEvalutionPoint;

	//�^�C�������`�F�b�N
	//n�^�[����ǂ� JudgeEvalution�ŗv�f���͒�`
	vector < int > tileMoveupCheck;

	vector<vector<pair<int,pair<int,int>>>>enemyMaxRoute;
	vector<int> enemyMaxGetPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};