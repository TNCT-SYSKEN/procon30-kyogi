#include"JudgeEvalution.h"
#define MAX_WIDTH 20
#define MAX_VERTICAL 20


void JudgeEvalution::calculateEnemyEvalution(vector<pair<int, pair<int,int>>>route,
	vector<pair<int, pair<int,int>>>moveUpTile,int moveup,int sum) {

	int getPoint = 0;
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Agents* agents;
	agents = agents->getAgents();


	int nowX = route[0].second.first;
	int nowY = route[0].second.second;

	//tiled　の複製
	vector<vector<int>>tiled(MAX_WIDTH ,vector<int>(MAX_VERTICAL));

	rep(i, map->width) {
		rep(j, map->vertical) {
			tiled[i][j] = field->tiled[i][j];
		}
	}
	//タイルポイント何点取れる
	rep(i, map->finalTurn - map->turn) {

		nowX += route[i + 1].second.first;
		nowY += route[i + 1].second.second;

		if (moveup > 0) {


			//タイル除去
			if ((i + 1) == moveUpTile[moveUpTile.size() - moveup].first) {
				//moveUpTileの
				tiled[moveUpTile[moveUpTile.size() - moveup].second.first][moveUpTile[moveUpTile.size() - moveup].second.second] = 0;
				getPoint += field->points[moveUpTile[moveUpTile.size() - moveup].second.first][moveUpTile[moveUpTile.size() - moveup].second.second];
			}
			else if (route[i + 1].second.first == 0 && route[i + 1].second.second == 0) {

			}
			else {
				tiled[nowX][nowY] = map->otherTeamID;
				getPoint += field->points[nowX][nowY];

				getPoint += calcAreaPoint(tiled, map->otherTeamID);
			}

		}
		else if (route[i + 1].second.first == 0 && route[i + 1].second.second == 0) {

		}
		else {
			tiled[nowX][nowY] = map->otherTeamID;
			getPoint += field->points[nowX][nowY];

			//1ターン先の領域ポイントの差分
			getPoint += calcAreaPoint(tiled, map->otherTeamID)-map->score[1][0];
		}
	}

	//もし最高得点の取れるルートならば
	if (getPoint > agentsEvalution->enemyMaxGetPoint[route[0].first - agents->otherAgents[0][0]]) {
		
		agentsEvalution->enemyMaxGetPoint[route[0].first - agents->otherAgents[0][0]] = getPoint;
		//enemy route更新
		agentsEvalution->enemyMaxRoute[route[0].first - agents->otherAgents[0][0]] = route;
		
	}



}




int JudgeEvalution::calcAreaPoint(vector<vector<int>>tiled, int agentsnum) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	vector<vector<int>> visited;
	visited.resize(map->width+2, vector<int>(map->vertical+2));
	rep(i, map->width + 2) {
		rep(j, map->vertical + 2) {
			if (i == 0 || i== map->width+1) visited[i][j] = 0;
			else if (j == 0 || j == map->vertical+1) visited[i][j] = 0;
			else {
				if (tiled[i - 1][j - 1]==agentsnum) {
					visited[i][j] = agentsnum;
				}
				else {

					visited[i][j] = 0;
				}
			}

		}
	}


	int dx[] = {1,0,0,-1};
	int dy[] = { 0,1,-1,0 };
	//踏んだら-1に
	visited[0][0] = -1;

	vector<pair<int, int>> stack;
	vector<pair<int, int>> stack2;
	stack[0] = make_pair(0, 0);
	int lastSize = 1;

	while (stack.size()!=0) {
		rep(i, lastSize) {
			rep(j, 4) {
				if (stack[i].first + dx[j] < map->vertical + 1 || stack[i].first + dx[j] >= 0
					|| stack[i].second+dy[j] < map->vertical+ 1 || stack[i].second+dy[j] >=0) {
					if (visited[stack[i].first + dx[j] + 1][stack[i].second + dy[j]+1]==0) {
						
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


