#pragma once
#include"Action_manager.h"

class Prefetching {
public:

	vector<vector<int>>hyoukaKeisan();

private:
	int calculateScore(pair<int,int>);
	pair<int,int> calculateEvalution(vector<pair<int,pair<int,int>>>,int,pair<int,int>,int,int);

	
};
