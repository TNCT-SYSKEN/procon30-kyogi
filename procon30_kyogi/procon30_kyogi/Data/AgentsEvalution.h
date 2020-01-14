#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//最高評価点ルート
	//{ (agentnum1) {(turn 1){agentnum1,{dx,dy}}, (turn 2){agentnum1,{dx,dy}},...} , (agentnum 2){(turn1)}}
	vector<vector<pair<int, pair<int, int>>>>maxRoute;
	float maxEvalutionPoint;

	vector<int>ourMaxGetPoint;
	vector<vector<pair<int, pair<int, int>>>>ourMaxRoute;

	//タイル除去チェック
	//nターン先読み JudgeEvalutionで要素数は定義
	vector < int > tileMoveupCheck;

	vector<vector<pair<int, pair<int, int>>>>enemyMaxRoute;
	vector<int> enemyMaxGetPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};