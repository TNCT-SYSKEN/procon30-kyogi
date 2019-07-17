#include"Hyouka.h"


//全てのエージェントについて一気に評価点計算をしたほうが
//場所変更などをしやすい

//評価点計算に必要な情報は
//フィールド情報、タイル状況、エージェントの位置
//自分のチームの得点、相手のチームの得点
//それぞれを引数として扱う

vector<vector<int>> Hyouka::hyoukaKeisan()
{
	Map *map;
	map = map->getMap();

	Hyouka::hyoukaPoint={};//評価点初期化


	int hyouka_p;
	

	

	

	return vector<vector<int>>();
}

int Hyouka::calculateScore(int x,int y)
{
	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();

	int sum = 0;

	if (x <= 0 || x > map->width || y <= 0 || y > map->vertical) {
		return -1;
	}
	else {
		field->points[x - 1][y - 1];
	}

	return sum;
}


