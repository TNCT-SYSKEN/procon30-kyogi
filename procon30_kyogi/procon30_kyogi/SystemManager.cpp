#include"SystemManager.h"

void SystemManager::systemManager() {

	Action_manager acManager;
	Map* map;
	map = map->getMap();

	
	if (map->isGameStarted) {

		if (map->turnFlg) {
			
			acManager.Action();
				
			//評価したのにもう一度評価しないようにする
			map->turnFlg = false;
			map->isCalcOurAction = true;

		}
		/*if (map->enemyJson && map->isCalcOurAction) {
			
			DebugSystem();
		
			map->isCalcOurAction = false;
			map->turnFlg = true;
		}
		*/
	}

}

//debug試合進行
void SystemManager::DebugSystem() {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();

	int ourNowX;
	int ourNowY;

	int otherNowX;
	int otherNowY;

	int AgentS = agents->ourAgents.size();
	
	bool OurAgentsCheck[8];
	bool OtherAgentsCheck[8];


	rep(i, 8) {
		OurAgentsCheck[i] = true;
		OtherAgentsCheck[i] = true;

	}

	
	for (int i = 0; i < AgentS; i++) {
		//	移動先重複判定
		for (int j = 0; j < AgentS;j++) {
			ourNowX = agents->ourAgents[i][1] - 1 + agentsAction->actionDxDy[i][0].second.first;
			ourNowY = agents->ourAgents[i][2] - 1 + agentsAction->actionDxDy[i][0].second.second;
			if (i != j) {
				if (ourNowX == agents->ourAgents[j][1] - 1 + agentsAction->actionDxDy[j][0].second.first &&
					ourNowY == agents->ourAgents[j][2] - 1 + agentsAction->actionDxDy[j][0].second.second) {
					OurAgentsCheck[i] = false;
				}
				if (ourNowX < 0 || ourNowX >= map->width || ourNowY < 0 || ourNowY >= map->vertical) {
					OurAgentsCheck[i] = false;
				}
			}
			
			
		}
	}
	//敵
	for (int i = 0; i < AgentS; i++) {
		otherNowX = agents->otherAgents[i][1] - 1 + agentsAction->actionEnemyDxDy[i].second.first;
		otherNowY = agents->otherAgents[i][2] - 1 + agentsAction->actionEnemyDxDy[i].second.second;

		rep(j, AgentS) {
			if (i != j) {
				if (otherNowX == agents->otherAgents[j][1] - 1 + agentsAction->actionEnemyDxDy[j].second.first &&
					otherNowY == agents->otherAgents[j][2] - 1 + agentsAction->actionEnemyDxDy[j].second.second) {
					OtherAgentsCheck[i] = false;
				}
				if (otherNowX < 0 || otherNowX >= map->width || otherNowY < 0 || otherNowY >= map->vertical) {
					OtherAgentsCheck[i] = false;
				}
				
			}
		}
	}

	rep(i, AgentS) {
		rep(j, AgentS) {
			ourNowX = agents->ourAgents[i][1] - 1 + agentsAction->actionDxDy[i][0].second.first;
			ourNowY = agents->ourAgents[i][2] - 1 + agentsAction->actionDxDy[i][0].second.second;

			otherNowX = agents->otherAgents[j][1] - 1 + agentsAction->actionEnemyDxDy[j].second.first;
			otherNowY = agents->otherAgents[j][2] - 1 + agentsAction->actionEnemyDxDy[j].second.second;

			if (ourNowX == otherNowX && ourNowY == otherNowY) {
				OurAgentsCheck[i] = false;
				OtherAgentsCheck[j] = false;
			}

		}
	}

	rep(i, AgentS) {
		ourNowX = agents->ourAgents[i][1] - 1 + agentsAction->actionDxDy[i][0].second.first;
		ourNowY = agents->ourAgents[i][2] - 1 + agentsAction->actionDxDy[i][0].second.second;
		
		if (OurAgentsCheck[i]) {
			if (field->tiled[ourNowX][ourNowY] == map->otherTeamID) {
				field->tiled[ourNowX][ourNowY] = 0;
			}
	//		else if(field->tiled[ourNowX][ourNowY] == map->ourTeamID){
	//			
	//		}
			else {
				//map->score[1][i] = ourNowY;
				field->tiled[ourNowY][ourNowX] = map->ourTeamID;
				agents->ourAgents[i][1] += agentsAction->actionDxDy[i][0].second.first;
				agents->ourAgents[i][2] += agentsAction->actionDxDy[i][0].second.second;
			}
		}
	}
	rep(i, AgentS) {
		otherNowX = agents->otherAgents[i][1] - 1 + agentsAction->actionEnemyDxDy[i].second.first;
		otherNowY = agents->otherAgents[i][2] - 1 + agentsAction->actionEnemyDxDy[i].second.second;

		if (OtherAgentsCheck[i]) {

			if (field->tiled[otherNowX][otherNowY] == map->ourTeamID) {
				field->tiled[otherNowX][otherNowY] = 0;
			}
			else if(field->tiled[otherNowX][otherNowY] == map->otherTeamID){

			}
			else {
				field->tiled[otherNowX][otherNowY] = map->otherTeamID;
				agents->otherAgents[i][1] += agentsAction->actionEnemyDxDy[i].second.first;
				agents->otherAgents[i][2] += agentsAction->actionEnemyDxDy[i].second.second;
			}
		}
	}


	//map->score.resize(2, vector<int>(3, 0));
	//map->score[0][0] = 0;
	//map->score[0][1] = 0;
	//map->score[0][2] = 0;

	//map->score[1][0] = 0;
	//map->score[1][1] = 0;
	////map->score[1][2] = 0;


	//rep(i, map->width) {
	//	rep(j, map->vertical) {
	//		if (field->tiled[i][j] == map->ourTeamID) {
	//			map->score[0][1] += field->points[i][j];
	//		}
	//		else if (field->tiled[i][j] == map->otherTeamID) {
	//			map->score[1][1] += field->points[i][j];
	//		}
	//			
	//	}
	//}
	//
	//map->score[0][2] = calculateAreaPoint(map->ourTeamID);
	//map->score[1][2] = calculateAreaPoint(map->otherTeamID);

	////map->score[1][2] = agents->otherAgents[0][1];

	//map->score[0][0] += map->score[0][1] + map->score[0][2];
	//map->score[1][0] += map->score[1][1] + map->score[1][2];

	map->turnFlg = true;
	map->turn++;
}


//デバッグ用の領域計算
int SystemManager::calculateAreaPoint(int ourTeamID) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();

	//領域ポイント
	int lastAreaPoint = 0;


	vector<vector<int>> tiledArea;
	tiledArea.resize(map->width + 2, vector<int>(map->vertical + 2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	
	//初期化
	rep(i, map->width + 2) {
		rep(j, map->vertical + 2) {
			tiledArea[i][j] = 0;
		}
	}

	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j] == ourTeamID)
			{
				tiledArea[i + 1][j + 1] = ourTeamID;
			}

		}
	}


	lastMove[0] = make_pair(0, 0);

	tiledArea[0][0] = -1;
	lastSize = 1;

	//lastMoveを更新した時にすぐに書き換えたくない
	vector<pair<int, int>>stac;


	while (1) {
		//脱出
		if (lastSize == 0) {
			goto calc;
		}
		int counter = 0;

		rep(i, lastSize) {
			rep(k, 4) {
				if (lastMove[i].first + ddx[k] <= map->width + 1 &&
					lastMove[i].first + ddx[k] >= 0 &&
					lastMove[i].second + ddy[k] <= map->vertical + 1 &&
					lastMove[i].second + ddy[k] >= 0) {


					if (tiledArea[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] == 0) {
						tiledArea[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] = -1;

						stac.push_back(make_pair(lastMove[i].first + ddx[k], lastMove[i].second + ddy[k]));
						//stac[counter].first = lastMove[i].first + ddx[k];
						//stac[counter].second = lastMove[i].second + ddy[k];
						counter++;

					}
				}
			}
		}
		//上書き
		if (counter == 0) { goto calc; }
		lastMove.resize(counter);
		lastMove = stac;

		lastSize = counter;
		stac.resize(0);

	}

	calc:;

	//領域計算
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (tiledArea[i + 1][j + 1] == 0) {

				lastAreaPoint += abs(field->points[i][j]);

			}

		}
	}
	//lastAreaPoint -= map->score[1][2] * map->readTurn;

	return lastAreaPoint;
}