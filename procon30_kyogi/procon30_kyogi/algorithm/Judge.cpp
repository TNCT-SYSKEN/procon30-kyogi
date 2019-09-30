#include"Judge.h"


//全てのエージェントについて一気に評価点計算をしたほうが
//場所変更などをしやすい

//評価点計算に必要な情報は
//フィールド情報、タイル状況、エージェントの位置
//自分のチームの得点、相手のチームの得点
//それぞれを引数として扱う




//全探索モード
void Judge::fullSearch() {

	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();


	//敵ルート
	vector<pair<int,pair<int,int>>>enemyRoute = {};
	int ourAgentsS = agents->ourAgents.size();

	pair<int,int>agentsPosition;
	for (int agentsnum = agents->otherAgents[0][0]; agentsnum < agents->otherAgents[0][0]; agentsnum++) {
		//agents[0][1]などにアクセス
		agentsPosition.first = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][1] - 1;
		agentsPosition.second = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][2] - 1;

		enemyRoute.push_back(make_pair(agentsnum, agentsPosition));
		//敵最適ルート初期化
		//	ここで先読みターン数に応じたサイズを初期化する
		agentsEvalution->enemyMaxRoute.resize(0);
		agentsPosition=

	}



}

void Judge::calculateTilePoint(vector<pair<int, pair<int, int>>>route,int teamID) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	
	int sum = 0;



	//残りのターン数だけ計算
	rep(counter,map->finalTurn - map->turn+1)
		rep(i, map->width) {
			rep(j, map->vertical) {
				if()
				
			}
		}

}



void Judge::calculateAreaPoint(vector<pair<int,pair<int,int>>>route,int teamID,int sum) {
	



}


void Judge::calculateEnemyEvalution(vector<pair<int, pair<int, int>>>route, int sum) {

}


