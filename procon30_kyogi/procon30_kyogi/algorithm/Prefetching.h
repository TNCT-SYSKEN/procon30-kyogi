#pragma once
#include"Action_manager.h"
#include"../gui/DrawData.h"
class Prefetching {
public:

	void hyoukaKeisan();
	int calculateScore(pair<int,int>,int);
private:
	
	void calculateEvalution(vector<pair<int,pair<int,int>>>,pair<int,int>,vector<vector<int>>,int, int,int);

	
};
