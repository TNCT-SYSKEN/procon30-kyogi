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
		if (map->enemyJson && map->isCalcOurAction) {
			/*DebugSystem();
		
			map->isCalcOurAction = false;
			map->turnFlg = true;*/
		}
		
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


	int AgentS = agents->ourAgents.size();
	rep(i, AgentS) {
		bool our = false;
		bool other = true;
		//	移動先重複判定
		rep(j, AgentS) {
			if (i != j) {
				//ourAgentと被らない
				if (agents->ourAgents[i][1] + agentsAction->actionDxDy[i][0].second.first != agents->ourAgents[j][1] + agentsAction->actionDxDy[j][0].second.first
					|| agents->ourAgents[i][2] + agentsAction->actionDxDy[i][0].second.second != agents->ourAgents[j][2] + agentsAction->actionDxDy[j][0].second.second) {
					our = true;
				}//otherAgentと被らない
				if (agents->otherAgents[i][1] + agentsAction->actionEnemyDxDy[i].second.first != agents->otherAgents[j][1] + agentsAction->actionEnemyDxDy[j].second.first
					|| agents->otherAgents[i][2] + agentsAction->actionEnemyDxDy[i].second.second != agents->otherAgents[j][2] + agentsAction->actionEnemyDxDy[j].second.second) {
					other = true;
				}
			}

			if (our && (agents->ourAgents[i][1] + agentsAction->actionDxDy[i][0].second.first != agents->otherAgents[j][1] + agentsAction->actionEnemyDxDy[i].second.first
				|| agents->ourAgents[i][2] + agentsAction->actionDxDy[i][0].second.second != agents->otherAgents[j][2] + agentsAction->actionEnemyDxDy[i].second.first)) {
				//ourAgents[i]は競合なし
				agents->ourAgents[i][1] += agentsAction->actionDxDy[i][0].second.first;
				agents->ourAgents[i][2] += agentsAction->actionDxDy[i][0].second.second;

				//ourAgents remove otherTiled
				if (field->tiled[agents->ourAgents[i][1] - 1][agents->ourAgents[i][2] - 1] == map->otherTeamID) {
					field->tiled[agents->ourAgents[i][1] - 1][agents->ourAgents[i][2] - 1] = 0;

					agents->otherAgents[i][1] -= agentsAction->actionDxDy[i][0].second.first;
					agents->otherAgents[i][2] -= agentsAction->actionDxDy[i][0].second.second;

				}
				else if (field->tiled[agents->ourAgents[i][1] - 1][agents->ourAgents[i][2] - 1] == map->ourTeamID) {
					agents->ourAgents[i][1] -= agentsAction->actionDxDy[i][0].second.first;
					agents->ourAgents[i][2] -= agentsAction->actionDxDy[i][0].second.second;
				}
				else {
					field->tiled[agents->ourAgents[i][1] - 1][agents->ourAgents[i][2] - 1] = map->ourTeamID;
				}
			}
			else if (other && (agents->otherAgents[i][1] + agentsAction->actionEnemyDxDy[i].second.first != agents->ourAgents[j][1] + agentsAction->actionDxDy[i][0].second.first
				|| agents->otherAgents[i][2] + agentsAction->actionEnemyDxDy[i].second.second != agents->ourAgents[j][2] + agentsAction->actionDxDy[i][0].second.first)) {

				//otherAgents[i]は競合なし
				agents->otherAgents[i][1] += agentsAction->actionEnemyDxDy[i].second.first;
				agents->otherAgents[i][2] += agentsAction->actionEnemyDxDy[i].second.second;

				//otherAgents remove otherTiled
				if (field->tiled[agents->otherAgents[i][1] - 1][agents->otherAgents[i][2] - 1] == map->ourTeamID) {
					field->tiled[agents->otherAgents[i][1] - 1][agents->otherAgents[i][2] - 1] = 0;

					agents->otherAgents[i][1] -= agentsAction->actionEnemyDxDy[i].second.first;
					agents->otherAgents[i][2] -= agentsAction->actionEnemyDxDy[i].second.second;

				}
				else if (field->tiled[agents->otherAgents[i][1] - 1][agents->otherAgents[i][2] - 1] == map->otherTeamID) {
					agents->otherAgents[i][1] -= agentsAction->actionEnemyDxDy[i].second.first;
					agents->otherAgents[i][2] -= agentsAction->actionEnemyDxDy[i].second.second;
				}
				else {
					field->tiled[agents->otherAgents[i][1] - 1][agents->otherAgents[i][2] - 1] = map->otherTeamID;
				}

			}
		}
	}

	map->score.resize(2, vector<int>(3, 0));
	rep(swi, 2) {
		rep(i, map->width) {
			rep(j, map->vertical) {
				map->score[swi][1] += field->points[i][j];
			}
		}
	}
	map->score[0][2] = calculateAreaPoint(map->ourTeamID);
	map->score[1][2] = calculateAreaPoint(map->otherTeamID);

	map->score[0][0] += map->score[0][1] + map->score[0][2];
	map->score[1][0] += map->score[1][1] + map->score[1][2];

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