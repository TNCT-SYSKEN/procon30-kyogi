#pragma once
#include"Action_manager.h"
#include"../Data/AgentsEvalution.h"
class Evalution {
public:
	//•]‰¿“_ŒvŽZ
	void calculateEvalution(vector<pair<int,pair<int,int>>>,vector<pair<int,pair<int,int>>>,int,int);


	int calculateAreaPoint(vector<pair<int,pair<int,int>>>,int);
	int calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>);

	
};