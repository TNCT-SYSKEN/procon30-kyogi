#pragma once
#include"ActionManager.h"
class Evalution {
public:
	//�]���_�v�Z
	void calculateEvalution(vector<pair<int,pair<int,int>>>,int);

private:
	int calculateAreaPoint(vector<pair<int,pair<int,int>>>);
};