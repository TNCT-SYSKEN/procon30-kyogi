#pragma once
#include"../general.h"
class AgentsEvalution {
public:
	//最高評価点ルート
	vector<pair<int, int>> maxRoute;
	float maxEvalutionPoint;

	//タイル除去チェック
	//nターン先読み JudgeEvalutionで要素数は定義
	vector < int > tileMoveupCheck;

	vector<vector<pair<int,pair<int,int>>>>enemyMaxRoute;
	vector<int> enemyMaxGetPoint;

	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};