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
			DebugSystem();
		}
		
	}

}

//debug試合進行
void SystemManager::DebugSystem() {

}


//デバッグ用の領域計算
int SystemManager::calcAreaDebug(int teamID) {

	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	int dx[] = { 1,0,0,-1 };
	int dy[] = { 0,1,-1,0 };


	vector<vector<int>> visited(map->width+2, vector<int>(map->vertical+2, 0));
	rep(i, map->width) {
		rep(j, map->width) {
			if (field->tiled[i][j] == teamID) {
				visited[i + 1][j + 1] = teamID;
			}
		}
	}

	visited[0][0] = -1;

	vector<pair<int, int>>search(1);
	vector<pair<int, int>>stac;
	search.push_back(make_pair(0, 0));
	int searchSize = 1;
	int searchX = 0;
	int searchY = 0;


	while (searchSize > 0) {
		rep(i, searchSize) {
			rep(turn, 4) {
				
				searchX = search[i].first + dx[turn];
				searchY = search[i].second + dy[turn];

				if (searchX > 0 && searchX <map->width+2 && searchY>0 && searchY <map->vertical+2) {
					if (visited[searchX][searchY]==0) {
						visited[searchX][searchY] = -1;
						stac.push_back(make_pair(searchX, searchY));
					}
				}
			}
		}

		search.resize(0);
		search = stac;
		searchSize = search.size();
	}
	
	int sum = 0;
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (visited[i+1][j+1] == 0) {

				sum += field->points[i][j];
			}
		}
	}

	return sum;

}