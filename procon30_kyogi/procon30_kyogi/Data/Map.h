#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//縦
	int vertical;
	//横
	int width;

	//自分のチームのスコア{総合点,タイル,領域},
	//相手				  {総合点,タイル,領域}
	vector<vector<int>> score;
	
	//ターン数
	int turn;

	int readTurn = 3;

	//自分チームID
	int ourTeamID;
	//相手チームID
	int otherTeamID;


private:
	static Map* stayMap;
};