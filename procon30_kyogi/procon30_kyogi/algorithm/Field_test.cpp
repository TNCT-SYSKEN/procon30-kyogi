#include"ActionManager.h"
#include"Field_test.h"
#include"../Data/Field.h"
#include"../Data/Agents.h"
#include"../Data/AgentsAction.h"
#include"../Data/Map.h"


//テスト用フィールド情報定義ファイル

void Field_test::fieldTest(){


	//about Map
	Map *map;
	map = map->getMap();
	map->width = 6;
	map->vertical = 4;
	map->turn = 0;
	//score
	//{総合点,タイル,領域}
	map->score = {
		{5,5,0},//自分
		{5,5,0}// 相手
	};
	//teamID
	map->ourTeaMID = 5;
	map->otherTeamID = 6;


	//about Agents
	Agents *agents;
	agents = agents->getAgents();
	agents->ourAgents= {
		{9,1,2},
		{10,4,4}
	};
	agents->otherAgents={ 
		{11,3,1},
		{12,6,3}
	};
	
	//about Field
	Field *field;
	field = field->getField();
	field->points={
		{ 2, -4, 0, 0, -4, 2 },
		{ 5, -1, 1, 1, -1, 5 },
		{ 5, -1, 1, 1, -1, 5 },
		{ 2, -4, 0, 0, -4, 2 }
	};
	field->tiled= {
		{0, 0, 6, 0, 0, 0},
		{5, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 6},
		{0, 0, 0, 5, 0, 0}
	};


	

}



