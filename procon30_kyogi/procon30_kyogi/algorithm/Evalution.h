#pragma once
#include"ActionManager.h"
class Evalution {
public:
	//�]���_�v�Z
	void calculateEvalution(vector<pair<int,pair<int,int>>> route,int readTurn,int sum);

private:
	int calculateAreaPoint();
};