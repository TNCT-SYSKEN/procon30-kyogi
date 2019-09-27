#include"Evalution.h"

int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

float evalution[4] = { 6,5,4,3, };
// 領域, 相手の点が高いか, 移動可能マス,　移動先の点数の高さ


float magnificat[] = { 1,1.5,1,1,1,1 };
/*
	倍率補正
	0 タイル除去するとき　tilePointをかける（小さめ）
	1 相手の領域ポイントが自分のものより高いとき
	2 相手のほうがポイントが高い

*/

void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, int sum)
{

	Map *map;
	map = map->getMap();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Field *field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();



	//エージェントがそのマスの付近にいたら評価を下げる（戦局次第では上げる）
	//相手がタイルポイント以上の点を取ったら領域を取ったものとみなし、
	//ポイントが大きければ大きいほど評価点の上がり調子も大きくする
	
	//自分のチームのtiledを踏もうとするときには評価点をめちゃ下げる
	//もしくは評価しない

	//評価点合計
	float sumOfEvalution = 0;


	//計算途中でのエージェントの動いた後のposition
	int nowX = route[0].second.first;
	int nowY = route[0].second.second;
	//敵タイル除去を行うかどうか
	rep(i, map->readTurn) {
		nowX+=route[i+1].second.first;
		nowY += route[i+1].second.second;
		if (field->tiled[nowX][nowY] == map->otherTeamID) {

			int areaEnemyPoint = calculateEnemyAreaPoint(route);
			/////////////////////////////////////////////////////
			if (areaEnemyPoint != 0) {

				sumOfEvalution += (float)(areaEnemyPoint*evalution[0]);
			}
			
			
			goto KUSA;
		}
	}
	KUSA:;

	//移動可能マス計算
	vector<vector<int>>tiledArea;
	rep(i, map->width) {
		rep(j, map->width) {
			if (tiledArea[i][j] == map->ourTeamID) {
				//味方タイル １
				tiledArea[i][j] = 1;
			}
			else if (tiledArea[i][j] == map->otherTeamID) {
				//相手タイル 2
				tiledArea[i][j] = 2;
			}

			tiledArea[i][j] = field->tiled[i][j];
		}
	}

	//エージェント回数ループ
	rep(i, agents->ourAgents.size()) {
		if (route[0].first != agents->ourAgents[i][0]) {
			//味方　３
			tiledArea[agents->ourAgents[i][1]][agents->ourAgents[i][2]] = 3;
		}
		//敵　５
		tiledArea[agents->otherAgents[i][1]][agents->otherAgents[i][2]] = 5;
		
	}

	nowX = route[0].second.first;
	nowY = route[0].second.second;
	//移動可能マス
	int canMove = 0;
	rep(i, map->readTurn) {

		//９方向
		rep(j, 9) {
			//マスがそとでないならば
			if (!(nowX + dx[j] < 0 && nowX + dx[j] < map->width
				&& nowY + dy[j] < 0 && nowY + dy[j] >map->vertical)) {
				if (tiledArea[nowX + dx[j]][nowY + dy[j]] == 1) {
				}
				else if(tiledArea[nowX+dx[j]][nowY+dy[j]]==3){
					canMove -= 2;
				}
				canMove++;
			}
		}

	}
	//移動可能マス評価加算
	sumOfEvalution += canMove * evalution[2];
	

	if (map->score[0][0] > map->score[1][0]) {
		sumOfEvalution += sum * evalution[3] * magnificat[2];
	}
	else {
		sumOfEvalution += sum * evalution[3];
	}
	



	int routeS = route.size() - 1;
	//Route更新（評価最大）
	if (agentsEvalution->maxEvalutionPoint < sumOfEvalution) {
		
		rep(i, routeS) {
			agentsEvalution->maxRoute[i] = route[i + 1].second;
		}
		
	}
	

}

//領域ポイント計算
int Evalution::calculateAreaPoint(vector<pair<int,pair<int,int>>>route) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	int nowX = route[0].second.first;
	int nowY = route[0].second.second;
	//領域チェックもしや
	bool IF = false;

	//相手の領域ポイント
	int lastAreaPoint = 0;


	pair<int,int> lastPos;


	vector<vector<int>>tiledArea;
	//初期化
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j]==0)
			{
				tiledArea[i][j] = 0;
			}
			else if(field->tiled[i][j]==map->ourTeamID)
			{
				tiledArea[i][j] = 1;
			}
		}
	}
	

	//先読みの数だけループ
	rep(count, map->readTurn) {
		nowX += route[count + 1].second.first;
		nowY += route[count + 1].second.second;


		tiledArea[nowX][nowY] = 1;



		//width 横
		rep(i, map->width) {
			IF = false;

			//verticala 縦
			rep(j, map->vertical) {
				if (tiledArea[i][j]==1) {
					if (IF) {

						//
						for (int last = lastPos.second; last < j; last++) {
							tiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					tiledArea[i][j] = 0;
				}
			}
		}

		//vertical 縦
		rep(j, map->vertical) {
			IF = false;

			//width 横
			rep(i, map->width) {
				if (tiledArea[i][j] == 1) {
					if (IF) {

						//
						for (int last = lastPos.first+1; last < i; last++) {
							tiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					tiledArea[i][j] = 0;
				}
			}
		}
		//領域計算
		rep(i, map->width) {
			rep(j, map->vertical) {
				if (tiledArea[i][j] == 5) {
					lastAreaPoint += field->points[i][j];
				}
			}
		}
		lastAreaPoint -= map->score[1][2];

	}

	return lastAreaPoint;
}

//敵タイル除去した時の敵領域ポイントの変化
int Evalution::calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>route) {
	Map *map;
	map = map->getMap();

	Field *field;
	field = field->getField();

	vector<vector<int>>enemyTiledArea;
	int nowX = route[0].second.first;
	int nowY = route[0].second.first;
	   

	bool IF = false;

	//相手の領域ポイント
	int lastAreaPoint = 0;

	pair<int, int> lastPos;



	//初期化
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j] == 0) {
				enemyTiledArea[i][j] = 0;

			}
			else if (field->tiled[i][j] == map->otherTeamID) {
				enemyTiledArea[i][j] = 1;

			}
		}
	}


	//先読みの数だけループ
	rep(count, map->readTurn) {
		nowX += route[count + 1].second.first;
		nowY += route[count + 1].second.second;


		if (enemyTiledArea[nowX][nowY]==1) {
			nowX -= route[count + 1].second.first;
			nowY -= route[count + 1].second.second;
		}

		enemyTiledArea[nowX][nowY] = 0;



		//width 横
		rep(i, map->width) {
			IF = false;

			//verticala 縦
			rep(j, map->vertical) {
				if (enemyTiledArea[i][j] == 1) {
					if (IF) {

						//
						for (int last = lastPos.second; last < j; last++) {
							enemyTiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					enemyTiledArea[i][j] = 0;
				}
			}
		}

		//vertical 縦
		rep(j, map->vertical) {
			IF = false;

			//width 横
			rep(i, map->width) {
				if (enemyTiledArea[i][j] == 1) {
					if (IF) {

						//
						for (int last = lastPos.first + 1; last < i; last++) {
							enemyTiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					enemyTiledArea[i][j] = 0;
				}
			}
		}
		//領域計算
		rep(i, map->width) {
			rep(j, map->vertical) {
				if (enemyTiledArea[i][j] == 5) {
					lastAreaPoint += field->points[i][j];
				}
			}
		}
		lastAreaPoint = map->score[0][2] - lastAreaPoint;

	}
	//最終的には相手の領域ポイントをどれだけ削れたかがわかる
	return lastAreaPoint;
}