#pragma once
#include"../general.h"

class Field_test {
public:

	//ここでフィールド情報をテスト用で定義

	int *width;
	int *height;
	//teamID
	int *my_teamID;
	int *other_teamID;

	//ポイント情報
	static vector<vector<int>>points;

	



	//エージェントID,x,y
	static vector<vector<int>>*agents;

	//タイル状況
	static vector<vector<int>>*tiled;

	//タイルポイント,領域ポイント,合計ポイント
	//自分のチーム
	static vector<int>*my_team_point;

	//相手のチーム
	static vector<int>*other_team_point;

	static void Field();
};


