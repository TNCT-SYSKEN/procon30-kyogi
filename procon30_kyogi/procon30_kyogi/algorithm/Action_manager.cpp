#include "Action_manager.h"//general.h, Field_test.h, Hyouka.h
//このファイルを実行することですべてのアルゴリズム処理を実行させる
//master的なファイル


//	1.評価計算
//	2.移動情報を表示


void Action_manager::Action()
{

	//Hyouka.cppの関数を呼び出す
	//現在の得点などをちゃんと別のファイル、もしくは関数で取得する必要がある。
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();

	Prefetching prefetching;
	Judge judge;

	//計算
	//全探索モードでなかったら
	if (map->isSearchAll) {
		prefetching.hyoukaKeisan();
	}
	else {
		judge.fullSearch();
	}


	//評価計算終わった後
	//turnAgent,turnTiledの更新
	int agentS = agents->ourAgents.size();

	field->turnAgent.resize(0);
	field->turnAgent.resize(map->readTurn + 1, vector<pair<int, int>>(agentS));

	field->turnTiled.resize(map->readTurn + 1, vector<vector<int>>(map->width, vector<int>(map->vertical)));

	int nowX[8], nowY[8];

	rep(i, agentS) {
		nowX[i] = agents->ourAgents[i][1];
		nowY[i] = agents->ourAgents[i][2];

		field->turnAgent[0][i] = make_pair(nowX[i], nowY[i]);
	}
	rep(turn, map->readTurn + 1) {
		field->turnTiled[turn] = field->tiled;
	}


	rep(turn, map->readTurn) {
		field->turnTiled[turn + 1] = field->turnTiled[turn];

		rep(agentnum, agentS) {
			nowX[agentnum] += agentsAction->actionDxDy[agentnum][turn].second.first;
			nowY[agentnum] += agentsAction->actionDxDy[agentnum][turn].second.second;

			/*if (field->turnTiled[turn + 1][nowX[agentnum]][nowY[agentnum]] == map->otherTeamID) {
				nowX[agentnum] -= agentsAction->actionDxDy[agentnum][turn].second.first;
				nowY[agentnum] -= agentsAction->actionDxDy[agentnum][turn].second.second;
			}*/

			field->turnTiled[turn + 1][nowX[agentnum]][nowY[agentnum]] = map->ourTeamID;

			field->turnAgent[turn + 1][agentnum] = make_pair(nowX[agentnum], nowY[agentnum]);
		}
	}


}
