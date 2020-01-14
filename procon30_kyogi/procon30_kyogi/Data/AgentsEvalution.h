#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//�ō��]���_���[�g
	//{ (agentnum1) {(turn 1){agentnum1,{dx,dy}}, (turn 2){agentnum1,{dx,dy}},...} , (agentnum 2){(turn1)}}
	vector<vector<pair<int, pair<int, int>>>>maxRoute;
	float maxEvalutionPoint;

	vector<int>ourMaxGetPoint;
	vector<vector<pair<int, pair<int, int>>>>ourMaxRoute;

	//�^�C�������`�F�b�N
	//n�^�[����ǂ� JudgeEvalution�ŗv�f���͒�`
	vector < int > tileMoveupCheck;

	vector<vector<pair<int, pair<int, int>>>>enemyMaxRoute;
	vector<int> enemyMaxGetPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};