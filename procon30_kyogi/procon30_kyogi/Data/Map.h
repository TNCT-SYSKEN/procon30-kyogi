#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//横
	int width;

	//縦
	int vertical;

	float startedAtUnixTime = 0;

	
	//自分のチームのスコア{総合点,タイル,領域},
	//相手				  {総合点,タイル,領域}
	vector<vector<int>> score;
	
	//ターン数
	int turn = 0;

	//先読みターン数
	int readTurn;

	//最終ターン数
	int finalTurn=20;

	//自分チームID
	int ourTeamID;
	//相手チームID
	int otherTeamID;

	//MapChange
	int mapChange=0;
	bool click;
	int x, y;



	//計算したかどうか
	bool turnFlg=false;
	bool isGameStarted=false;
	bool isSearchAll=false;
	bool makeReadTurnMap=false;
	//最初のjsonfile 読み取り
	bool firstJson=false;
	//debug 相手のjsonが来たかどうか判定
	bool enemyJson = false;
	
	//debugMode
	bool isDebug = true;
	//debug そのターンにエージェントの評価計算したかどうか
	bool isCalcOurAction = false;

private:
	static Map* stayMap;
};