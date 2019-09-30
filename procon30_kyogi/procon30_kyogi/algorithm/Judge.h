#pragma once
#include"Action_manager.h"
#include"JudgeEvalution.h"

class Judge {
public:
	//評価点計算に必要な情報は
	//フィールド情報、タイル状況、エージェントの位置
	//自分のチームの得点、相手のチームの得点
	//それぞれを引数として扱う

	void fullSearch();



private:
	
	void calculateEnemyRoute(vector<pair<int, pair<int,int>>>,pair<int,int>,vector<pair<int,pair<int,int>>>,int ,int, int);
	void calculateAreaPoint(vector<pair<int, pair<int, int>>>, int,int);
	void calculateTilePoint(vector<pair<int, pair<int, int>>>, int);
	
};
