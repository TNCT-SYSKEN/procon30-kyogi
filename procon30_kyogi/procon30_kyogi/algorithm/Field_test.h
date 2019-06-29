#pragma once
#include"../general.h"

class Field_test {
public:

	//ここでフィールド情報をテスト用で定義

	int width = 6;
	int height = 4;
	//teamID
	int my_teamID = 5;
	int other_teamID = 9;

	//ポイント情報
	vector<vector<int>>points{
		{2, -4, 0, 0, -4, 2},
		{5, -1, 1, 1, -1, 5},
		{5, -1, 1, 1, -1, 5},
		{2, -4, 0, 0, -4, 2}
	};
	
	//エージェントID,x,y
	vector<vector<int>>agents{
		{9,1,2},
		{10,4,4},
		{11,3,1},
		{12,6,3}
	};
	

	//タイルポイント,領域ポイント,合計ポイント
	
	//自分のチーム
	vector<int>my_team_point{
		5,0,5
	};
	//相手のチーム
	vector<int>other_team_point{
		5,0,5
	}

};

