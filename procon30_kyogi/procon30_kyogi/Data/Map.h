#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//横
	int width;

	//縦
	int vertical;

	//Unix時間
	float startedAtUnixTime = 0;


	//自分のチームのスコア{総合点,タイル,領域},
	//相手				  {総合点,タイル,領域}
	vector<vector<int>> score;

	//ターン数
	int turn = 0;

	//先読みターン数
	int readTurn;

	//最終ターン数
	int finalTurn = 20;

	//自分チームID
	int ourTeamID;
	//相手チームID
	int otherTeamID;

	//MapChange
	int mapChange = 0;
	bool click;
	int x, y;

	//領域計算ONOFF
	bool calcArea = false;


	//計算したかどうか
	bool turnFlg = false;

	bool isSearchAll = false;
	bool makeReadTurnMap = false;
	//最初のjsonfile 読み取り
	bool firstJson = false;
	//debug 相手のjsonが来たかどうか判定
	bool enemyJson = false;

	//debug そのターンにエージェントの評価計算したかどうか
	bool isCalcOurAction = false;


	int makeJsonCount = 0;


	bool AnalysFieled = false;
	bool AnalysCalcC = false;


	string token = "dbc07e57a1e7b1342c0570d0a4393a53bef552ac2c900f3d2c21dd68a40f3d8b";
	string matchNumber;

private:
	static Map* stayMap;
};