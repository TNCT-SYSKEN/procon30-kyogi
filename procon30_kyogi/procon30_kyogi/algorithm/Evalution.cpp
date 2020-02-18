#include"Evalution.h"


float evalution[] = { 6,5,1.8,3,2.3 ,4 };
// 0. 領域, 相手の点が高いか, 移動可能マス,　移動先の点数の高さ,タイル除去,外側に行こうとしているか, 6. Analysis


float magnificat[] = { 1.1 , 1.2,1,1,1,1 };
/*
	倍率補正
	0 タイル除去するとき　tilePointをかける（小さめ）
	1 相手の領域ポイントが自分のものより高いとき
	2 相手のほうがポイントが高い

*/

void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, vector<vector<vector<int>>>moveUpTile, int agentsnum, int sum)
{

	Map *map;
	map = map->getMap();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	


	//エージェントがそのマスの付近にいたら評価を下げる（戦局次第では上げる）
	//相手がタイルポイント以上の点を取ったら領域を取ったものとみなし、
	//ポイントが大きければ大きいほど評価点の上がり調子も大きくする

	// ↓ 評価を普通くらいにする
	//自分のチームのtiledを踏もうとするときには評価点をめちゃ下げる
	//もしくは評価しない

	int routeS = map->readTurn;
	//Route更新（評価最大）


	if (agentsEvalution->maxEvalutionPoint < sumOfEvalution) {

		//map->score[1][2]++;
		agentsEvalution->maxEvalutionPoint = sumOfEvalution;

		agentsEvalution->maxRoute[agentsnum].resize(0);
		rep(i, routeS) {
			// 初期位置は追加しない
			agentsEvalution->maxRoute[agentsnum].push_back(route[i + 1]);
		}
	}

}



// フィールド評価point計算
void Evalution::calculateEvalutionPoint()
{
	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();


	/*  移動可能マス計算	*/
	vector<vector<int>>agentsPositionField(map->width, vector<int>(map->vertical,0));

	//エージェント回数ループ
	int agentsSize = agents->ourAgents.size();
	rep(i, agentsSize) {
		//味方　-2
		agentsPositionField[agents->ourAgents[i][1]][agents->ourAgents[i][2]] = -2;
		
		//敵　-3
		agentsPositionField[agents->otherAgents[i][1]][agents->otherAgents[i][2]] = -3;

	}
	//移動可能マス
	float canMove = 0;



	rep(i, map->width) {
		rep(j, map->vertical) {
			
			

			// Analys POINT
			if (map->AnalysField == true) {
				field->evalutionField[i][j] += field->AnalysisField[i][j] * evalution[6];
			}

			//相手タイル除去の場合
			if (field->tiled[i][j] == map->otherTeamID) {

				field->evalutionField[i][j] += field->points[i][j]* evalution[4] * magnificat[0];
				
			}
			// 自チームタイルの場合
			else if (field->tiled[i][j] == map->ourTeamID) {
				field->evalutionField[i][j] += 0;
			}
			else {

				// 相手より高いかどうかで評価に倍率補正がかかる
				if (map->score[0][0] < map->score[1][0]) {
					// tile POINT
					field->evalutionField[i][j] = field->points[i][j] * evalution[3] * magnificat[2];
				}
				else {
					// tile POINT
					field->evalutionField[i][j] = field->points[i][j] * evalution[3];
				}
			}

			//端に行くほど評価点は高くなる
			field->evalutionField[i][j] += (abs(i - map->width / 2) + abs(j - map->vertical / 2))* evalution[5];
		
			// 移動可能マス計算
			//９方向
			rep(count, 9) {
				//マスがそとでないならば
				int newX = i + dx[count];
				int newY = j + dy[count];

				if (newX >= 0 && newX < map->width
					&& newY >= 0 && newY < map->vertical) {

					if (agentsPositionField[newX][newY] == -2 || field->tiled[newX][newY]== map->ourTeamID) {
						
						// エージェントなら
						if (agentsPositionField[newX][newY] == -2) {
							canMove += 0;
						}
						else {
							canMove++;
						}
					}
					else if (agentsPositionField[newX][newY] ==-3 || field->tiled[newX][newY] == map->otherTeamID) {
						canMove += 0.5;
					}
					else {
						canMove++;
					}
				}
			}
		
		}
	}
	
	

	
}









//領域計算の封印
/*

//領域ポイント計算
int Evalution::calculateAreaPoint(vector<vector<int>> moveUpTile) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	//相手の領域ポイント
	int lastAreaPoint = 0;




	vector<vector<int>> agentsPositionField;
	agentsPositionField.resize(map->width + 2, vector<int>(map->vertical + 2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	//先読みの数だけループ
	//初期化
	rep(i, map->width + 2) {
		rep(j, map->vertical + 2) {
			agentsPositionField[i][j] = 0;
		}
	}

	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j] == map->ourTeamID)
			{
				agentsPositionField[i + 1][j + 1] = map->ourTeamID;
			}

		}
	}


	lastMove[0] = make_pair(0, 0);


	agentsPositionField[0][0] = -1;
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


					if (agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] == 0) {
						agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] = -1;

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
			if (agentsPositionField[i + 1][j + 1] == 0) {

				lastAreaPoint += abs(field->points[i][j]);

			}

		}
	}
	lastAreaPoint -= map->score[0][2];

	return lastAreaPoint;
}





//敵タイル除去した時の敵領域ポイントの変化
int Evalution::calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>route) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	//int nowX = route[0].second.first;
	//int nowY = route[0].second.second;



	//相手の領域ポイント
	int lastAreaPoint = 0;




	vector<vector<int>> agentsPositionField;
	agentsPositionField.resize(map->width + 2, vector<int>(map->vertical + 2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	//先読みの数だけループ
	rep(count, map->readTurn) {
		//初期化
		rep(i, map->width + 2) {
			rep(j, map->vertical + 2) {
				agentsPositionField[i][j] = 0;
			}
		}

		rep(i, map->width) {
			rep(j, map->vertical) {
				if (field->tiled[i][j] == map->otherTeamID)
				{
					agentsPositionField[i + 1][j + 1] = map->otherTeamID;
				}

			}
		}


		lastMove[0] = make_pair(0, 0);

		agentsPositionField[0][0] = -1;
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


						if (agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] == 0) {
							agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] = -1;

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




	}
	//領域計算
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (agentsPositionField[i + 1][j + 1] == 0) {

				lastAreaPoint += abs(field->points[i][j]);

			}

		}
	}
	//lastAreaPoint -= map->score[1][2] * map->readTurn;

	return lastAreaPoint;
}

*/