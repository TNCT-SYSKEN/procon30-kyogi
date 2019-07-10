#include"Hyouka.h"


//全てのエージェントについて一気に評価点計算をしたほうが
//場所変更などをしやすい

//評価点計算に必要な情報は
//フィールド情報、タイル状況、エージェントの位置
//自分のチームの得点、相手のチームの得点
//それぞれを引数として扱う

vector<vector<int>> Hyouka::hyouka_keisan(vector<vector<int>>field, vector<vector<int>>hoge, vector<vector<int>>agents, vector<int>my_team_point, vector<int>other_team_point)
{
	//フィールド情報		field
	//タイル状況			tiled
	//エージェントの位置	agents
	//自得点				my_team_point
	//相得点				other_team_point


	Hyouka::hyouka_point={};//評価点初期化

	int agents_num = agents[0][0];
	int hyouka_p;
	

	int max_value = 0;//最大評価点
	//エージェントの数だけ評価点計算
	rep(i, agents.size()) {
		hyouka_p = 0;
		

	}

	

	return vector<vector<int>>();
}

