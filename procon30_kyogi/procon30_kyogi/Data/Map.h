#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//縦
	int vertical;
	//横
	int width;



	Map(): score(2,vector<int>(3,0)){};

	
	//自分のチームのスコア{総合点,タイル,領域},
	//相手				  {総合点,タイル,領域}
	vector<vector<int>> score;
	
	//ターン数
	int turn = 0;

	//先読みターン数
	int readTurn;

	//最終ターン数
	int finalTurn;

	//自分チームID
	int ourTeamID;
	//相手チームID
	int otherTeamID;



	//計算したかどうか
	bool turnFlg;
	bool isGameStarted;

private:
	static Map* stayMap;
};