#include"Judge.h"


//全てのエージェントについて一気に評価点計算をしたほうが
//場所変更などをしやすい

//評価点計算に必要な情報は
//フィールド情報、タイル状況、エージェントの位置
//自分のチームの得点、相手のチームの得点
//それぞれを引数として扱う



//注意
//踏んだ後のタイルをもう一度取るかもしれない
//


//全探索モード
void Judge::fullSearch() {


	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();


	//敵ルート
	vector<pair<int,pair<int,int>>>enemyRoute(1);
	int ourAgentsS = agents->ourAgents.size();

	//タイル除去したマスの座標、先読みターン数の記録
	vector<pair<int, pair<int, int>>>moveUpTile;

	pair<int,int>agentsPosition;
	for (int agentsnum = agents->otherAgents[0][0]; agentsnum < agents->otherAgents[0][0]; agentsnum++) {
		//agents[0][1]などにアクセス
		agentsPosition.first = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][1] - 1;
		agentsPosition.second = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][2] - 1;

		enemyRoute.push_back(make_pair(agentsnum, agentsPosition));
		//敵最適ルート初期化
		
		/*	ここで先読みターン数に応じたサイズを初期化する	*/
		agentsEvalution->maxRoute.resize(map->finalTurn - map->turn);
		agentsEvalution->maxEvalutionPoint = 0;
		agentsEvalution->enemyMaxRoute.resize(0);
		agentsEvalution->enamyMaxEvalutionPoint = 0;
		

		


		
		//行動予測
		calculateEnemyRoute(enemyRoute, agentsPosition,moveUpTile ,0,map->finalTurn-map->turn, 0);


	}



}





void Judge::calculateEnemyRoute(vector<pair<int, pair<int, int>>>route, pair<int, int> nowAgentPosition,
	vector<pair<int, pair<int, int>>>moveUpTile, int moveup, int readTurn, int sum) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();


	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	bool moveCheck = false;

	int movedTiled[20][20];
	rep(i, map->width) {
		rep(j, map->vertical) {
			movedTiled[i][j] = field->tiled[i][j];
		}
	}

	rep(turn, 9) {
		

		if (nowAgentPosition.first + dx[turn] < 0 || nowAgentPosition.first + dx[turn] >= map->width
			|| nowAgentPosition.second + dy[turn] < 0 || nowAgentPosition.second + dy[turn] >= map->vertical) {
			goto CantGoThere;
		}
		//踏んだのが敵（自身）のタイルだったらアクセスしない
		if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->otherTeamID) {
			if (turn == 4) {

			}
			else {

				goto CantGoThere;
			}
		}

		if (turn == 4) {

		}
		else {


			if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->ourTeamID) {
				//moveupのresize

				if (readTurn > 0) {
					moveUpTile.resize(moveup + 1);

					//1,2,3,4,5
					moveUpTile[moveup] = make_pair(map->finalTurn - map->turn + 1 - readTurn,
						(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]));
					moveup++;
					moveCheck = true;
					movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]];
				}
				
			}
			else {

				nowAgentPosition.first += dx[turn];
				nowAgentPosition.second += dy[turn];
			}	
		}
		//routeサイズ調整
		

		if (readTurn > 0) {
			
			route.resize(route.size()+1);
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			readTurn--;
			calculateEnemyRoute(route, nowAgentPosition, moveUpTile, moveup, readTurn, sum);
		}
		else {
			JudgeEvalution judgeEvalution;
			judgeEvalution.calculateEnemyEvalution(route, moveUpTile, moveup, sum);

		}
	

		//ひとつ前を消す
		route.resize(route.size() - 1);
	CantGoThere:;
	}



	
}


