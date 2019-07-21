#pragma once
#include"ActionManager.h"

class Prefetching {
public:

	vector<vector<int>>hyoukaKeisan();

private:
	int calculateScore(pair<int,int>);
	vector<int> calculateEvalution(vector<pair<int,pair<int,int>>>,int,pair<int,int>,int,int);


};
