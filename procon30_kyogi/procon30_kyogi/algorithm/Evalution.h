#pragma once
#include"Action_manager.h"
#include"../Data/AgentsEvalution.h"
class Evalution {
public:
	//�]���_�v�Z
	void calculateEvalution(vector<vector<pair<int,int>>>, float);
	float calculateEvalutionPoint(int,int, vector<pair<int,int>>);


	//int calculateAreaPoint(vector<vector<int>>);
	//int calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>);


};