#pragma once
#include"Action_manager.h"
#include"../gui/DrawData.h"
class Prefetching {
public:

	void hyoukaKeisan();

private:
	int calculateScore(pair<int,int>,int);
	void calculateEvalution(vector<pair<int,pair<int,int>>>,pair<int,int>,vector<pair<int,pair<int,int>>>,int, int,int);

	
};
