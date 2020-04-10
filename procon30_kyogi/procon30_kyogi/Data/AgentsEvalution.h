#pragma once
#include"../general.h"
class AgentsEvalution {
public:

	/*************** new ver*************/

	
	//最高評価点ルート
	//{ (agentnum1) {(turn 1){agentnum1,{dx,dy}}, (turn 2){agentnum1,{dx,dy}},...} , (agentnum 2){(turn1)}}
	vector<vector<pair<int, int>>>maxRoute;
	float maxEvalutionPoint;

	// 評価点計算の時のターン先読みタイル状況
	vector<vector<int>> turnTiledField;


	/************* judge *******************/


	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};