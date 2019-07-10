#pragma once
#include"Action_manager.h"

class Hyouka {
public:
	//評価点計算に必要な情報は
	//フィールド情報、タイル状況、エージェントの位置
	//自分のチームの得点、相手のチームの得点
	//それぞれを引数として扱う

	vector<vector<int>>hyouka_keisan(vector < vector<int>>, vector<vector<int>>, vector<vector<int>>, vector<int>, vector<int>);
	vector<vector<int>>hyouka_point;//評価点が入る

};
