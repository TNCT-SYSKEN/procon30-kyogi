#pragma once
#include"Action_manager.h"
#include"../Data/AgentsEvalution.h"
class Evalution {
public:
	//�]���_�v�Z
	void calculateEvalution(vector<pair<int,pair<int,int>>>,vector<vector<int>>,int,int);


	int calculateAreaPoint(vector<vector<int>>);
	int calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>);

	
};