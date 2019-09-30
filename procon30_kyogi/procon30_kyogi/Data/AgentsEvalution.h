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

	vector<pair<int, int>>enemyMaxRoute;
	float enamyMaxEvalutionPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};