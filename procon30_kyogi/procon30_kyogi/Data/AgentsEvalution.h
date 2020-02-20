#pragma once
#include"../general.h"
class AgentsEvalution {
public:

	/*************** new ver*************/

	//先読み1~4ターンでうまく調節
	// <agentnum <xy1 <xy2 <xy3 <xy4> >>>>
	float readTurnEvalutionPointDP[8][9][9][9][9];
	//最高評価点ルート
	//{ (agentnum1) {(turn 1){agentnum1,{dx,dy}}, (turn 2){agentnum1,{dx,dy}},...} , (agentnum 2){(turn1)}}
	vector<vector<pair<int, pair<int, int>>>>maxRoute;
	float maxEvalutionPoint;

	// 評価点計算の時のターン先読みタイル状況
	vector<vector<int>> turnTiledField;


	/************* judge *******************/


	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};