#pragma once
#include"Action_manager.h"
#include"../gui/DrawData.h"
class Prefetching {
public:

	void prefetching();

	void changeDestination();

private:
	void calculatePrefetching(vector<vector<pair<int,int>>>,vector<pair<int,int>>,vector<vector<int>>,int);

};
