#include"CreateMap.h"

/*****************このファイルの関数はDrawMap.cppからしか呼び出されない**************/

// フィールドの枠線draw
// drawMapFrame() -> 
void CreateMap::createMapFrame(const int vertical, const int side) {
	int k, c;
	for (int i = 0; i < side + 1; i++) {
		k = 600 + 60 * i;
		c = 40 * vertical;
		
		Line(k, 30, k, c + 30).draw(5);
		
	}

	for (int i = 0; i < vertical + 1; i++) {
		k = 40 * (i + 1);
		c = 60 * side;
		//1
		Line(600, k - 10, c + 600, k - 10).draw(5);
		
	}
}

// tiled 状況 draw
//ColorMap1
void CreateMap::createMapState(const int state, const int x, const int y) {
	Rect rect(600 + 60 * (x), 30 + 40 * (y), 60, 40);
	Map* map;
	map = map->getMap();
	if (state == map->ourTeamID) {
		// us
		rect.draw(Palette::Blue);
	}
	else if (state == map->otherTeamID) {
		// enemy
		rect.draw(Palette::Red);
	}
	else if (state == -1) {
		//エージェント選択モード（移動方向変更可能）
		rect.draw(Palette::Yellow);
	}
	else {
		// BackGround Color
		rect.draw(Palette::Black);
	}
}

// AgentPosition draw
//AgentsMap1
void CreateMap::createMapAgent(const int who, const int x, const int y) {
	Circle circle(600 + 60 * (x) + 20, 30 + 40 * (y) + 20, 15);
	
	switch (who) {
	case 1:
		// us
		circle.draw(Palette::Lightskyblue);
		break;
	case 2:
		//enemy
		circle.draw(Palette::Pink);
		break;
	}
}

//PointMap
void CreateMap::createMapPoint(const int point, const int x, const int y) {
	if (point >= 0) {
		font(point).draw(600 + 60 * (x) + 12, 30 + 40 * (y) - 2, Palette::White);
	}
	else {
		font(point).draw(600 + 60 * (x) + 4, 30 + 40 * (y) - 2, Palette::White);
	}
}

//移動先表示
//LineMap
void CreateMap::createMapLine(const int x1, const int y1, const int x2, const int y2) {
	Line(600 + 60 * (x1) + 20, 30 + 40 * (y1) + 20, 600 + 60 * (x2) + 20, 30 + 40 * (y2) + 20).draw(5, Palette::White);
}


/*
void CreateMap::createTurnField() {

	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();
	AgentsAction* agentsAcn;
	agentsAcn = agentsAcn->getAgentsAction();

	int agentS = agents->ourAgents.size();
	field->turnAgent.resize(map->readTurn+1, vector<pair<int, int>>(agentS));
	agentsAcn->actionDxDy.resize(agentS, vector<pair<int, pair<int, int>>>(map->readTurn+1 , pair<int, pair<int, int>>(0, pair<int, int>(0, 0))));

	int nowX[8];
	int nowY[8];

	rep(i, agentS) {
		nowX[i] = agents->ourAgents[i][1]-1;
		nowY[i] = agents->ourAgents[i][2]-1;
		field->turnAgent[0][i] = make_pair(nowX[i], nowY[i]);
	}

	field->turnTiled[0] = field->tiled;


	rep(turn, map->readTurn) {
		rep(agentnum, agentS) {
			nowX[agentnum] += agentsAcn->actionDxDy[agentnum][turn+1].second.first;
			nowY[agentnum] += agentsAcn->actionDxDy[agentnum][turn+1].second.second;

			if (field->turnTiled[turn+1][nowX[agentnum]][nowY[agentnum]] == map->otherTeamID) {
				field->turnTiled[turn][nowX[agentnum]][nowY[agentnum]] = 0;
				nowX[agentnum] -= agentsAcn->actionDxDy[agentnum][turn + 1].second.first;
				nowY[agentnum] -= agentsAcn->actionDxDy[agentnum][turn + 1].second.second;
			}
			else {
				field->turnTiled[turn + 1][nowX[agentnum]][nowY[agentnum]] = map->ourTeamID;
			}

			field->turnAgent[turn + 1][agentnum] = make_pair(nowX[agentnum], nowY[agentnum]);

		}
	}


}



*/
