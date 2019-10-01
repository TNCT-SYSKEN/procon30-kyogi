#pragma once
#include"Action_manager.h"

class JudgeEvalution {
public:
	void calculateEnemyEvalution(vector<pair<int, pair<int,int>>>,vector<pair<int, pair<int,int>>>,int,int);
	int calcAreaPoint(vector<vector<int>>, int);
};