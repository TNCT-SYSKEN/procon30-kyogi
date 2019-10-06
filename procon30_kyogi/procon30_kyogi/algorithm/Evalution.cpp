#include"Evalution.h"


float evalution[4] = { 6,5,4,3, };
// 領域, 相手の点が高いか, 移動可能マス,　移動先の点数の高さ


float magnificat[] = { 1,1.5,1,1,1,1 };
/*
	倍率補正
	0 タイル除去するとき　tilePointをかける（小さめ）
	1 相手の領域ポイントが自分のものより高いとき
	2 相手のほうがポイントが高い

*/

void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route,vector<pair<int,pair<int,int>>>moveUpTile,int moveup,int sum)
{

	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };


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

	
	//map->score[1][2] = calculateEnemyAreaPoint(route);
	
	int lastGetEnemyAreaPointR = map->score[1][2];
	//敵タイル除去を行うかどうか
	rep(i, map->readTurn) {

		if (field->tiled[nowX + route[i + 1].second.first][nowY+ route[i + 1].second.second] == map->otherTeamID) {

			int areaenemypoint = map->score[0][2] - calculateEnemyAreaPoint(route);
			
			/////////////////////////////////////////////////////
			if (areaenemypoint > 0) {
	
				sumOfEvalution += (float)(areaenemypoint*evalution[0]);
			}
			
		}
		nowX+=route[i+1].second.first;
		nowY += route[i+1].second.second;
	}


	//移動可能マス計算
	vector<vector<int>>tiledArea;
	tiledArea.resize(map->width, vector<int>(map->vertical));

	rep(i, map->width) {
		rep(j, map->width) {
			if (tiledArea[i][j] == map->ourTeamID) {
				//味方タイル １
				tiledArea[i][j] = map->ourTeamID;
			}
			else if (tiledArea[i][j] == map->otherTeamID) {
				//相手タイル 2
				tiledArea[i][j] = map->otherTeamID;
			}

			tiledArea[i][j] = field->tiled[i][j];
		}
	}

	//エージェント回数ループ

	int agentsSize = agents->ourAgents.size();
	rep(i, agentsSize) {
		if (route[0].first != agents->ourAgents[i][0]) {
			//味方　-2
			tiledArea[agents->ourAgents[i][1]-1][agents->ourAgents[i][2]-1] = -2;
		}
		//敵　-3
		tiledArea[agents->otherAgents[i][1]-1][agents->otherAgents[i][2]-1] = -3;
		
	}

	nowX = route[0].second.first;
	nowY = route[0].second.second;
	//移動可能マス
	int canMove = 0;
	rep(i, map->readTurn) {

		//９方向
		rep(j, 9) {
			//マスがそとでないならば
			if (nowX + dx[j] > 0 && nowX + dx[j] <= map->width
				&& nowY + dy[j] > 0 && nowY + dy[j] <= map->vertical) {
				if (tiledArea[nowX + dx[j]][nowY + dy[j]] == map->ourTeamID) {
				}
				else if(tiledArea[nowX+dx[j]][nowY+dy[j]]==map->otherTeamID){
					canMove --;
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
	



	int routeS = map->readTurn;
	//Route更新（評価最大）
	if (agentsEvalution->maxEvalutionPoint < sumOfEvalution) {
		
		int R = route[0].first - agents->ourAgents[0][0];
		rep(i, routeS) {
			agentsEvalution->maxRoute[R][i] = route[i+1];
		}
		
	}
	

}











//領域ポイント計算
int Evalution::calculateAreaPoint(vector<pair<int,pair<int,int>>>route,int teamID) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	vector<vector<int>> visited;
	visited.resize(map->width + 2, vector<int>(map->vertical + 2));
	rep(i, map->width + 2) {
		rep(j, map->vertical + 2) {
			if (i == 0 || i == map->width + 1) visited[i][j] = 0;
			else if (j == 0 || j == map->vertical + 1) visited[i][j] = 0;
			else {
				if (field->tiled[i - 1][j - 1] == teamID) {
					visited[i][j] = teamID;
				}
				else {

					visited[i][j] = 0;
				}
			}

		}
	}


	int dx[] = { 1,0,0,-1 };
	int dy[] = { 0,1,-1,0 };
	//踏んだら-1に
	visited[0][0] = -1;

	vector<pair<int, int>> stack;
	vector<pair<int, int>> stack2;
	stack[0] = make_pair(0, 0);
	int lastSize = 1;

	while (stack.size() != 0) {
		rep(i, lastSize) {
			rep(j, 4) {
				if (stack[i].first + dx[j] < map->vertical + 1 || stack[i].first + dx[j] >= 0
					|| stack[i].second + dy[j] < map->vertical + 1 || stack[i].second + dy[j] >= 0) {
					if (visited[stack[i].first + dx[j] + 1][stack[i].second + dy[j] + 1] == 0) {

						stack2.push_back(make_pair(stack[i].first + dx[j] + 1, stack[i].second + dy[j] + 1));
						visited[stack[i].first + dx[j] + 1][stack[i].second + dy[j] + 1] = -1;
					}

				}
			}
		}
		//stack２のサイズに変更
		stack.resize(stack2.size());
		stack = stack2;
		//stack2初期化
		stack2.resize(0);
		lastSize = stack.size();

	}


	int sum = 0;
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (visited[i + 1][j + 1] == 0) {
				sum += field->points[i][j];
			}
		}
	}
	return sum;
}



//敵タイル除去した時の敵領域ポイントの変化
int Evalution::calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>route) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	int nowX = route[0].second.first;
	int nowY = route[0].second.second;



	//相手の領域ポイント
	int lastAreaPoint = 0;




	vector<vector<int>> tiledArea;
	tiledArea.resize(map->width+2, vector<int>(map->vertical+2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	//先読みの数だけループ
	rep(count, map->readTurn) {
		//初期化
		rep(i, map->width + 2) {
			rep(j, map->vertical + 2) {
				tiledArea[i][j] = 0;
			}
		}

		rep(i, map->width) {
			rep(j, map->vertical) {
				if (field->tiled[i][j] == map->otherTeamID)
				{
					tiledArea[i + 1][j + 1] =map-> otherTeamID;
				}

			}
		}


		lastMove[0] = make_pair(0, 0);

		nowX += route[count + 1].second.first;
		nowY += route[count + 1].second.second;

		tiledArea[nowX + 1][nowY + 1] = 0;
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
						lastMove[i].first + ddx[k] >=0 &&
						lastMove[i].second + ddy[k] <= map->vertical + 1 &&
						lastMove[i].second + ddy[k]>=0) {


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




	}
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