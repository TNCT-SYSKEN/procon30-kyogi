#include"CreateMap.h"

#include"../Data/Agents.h"

//MapFrame
void CreateMap::createMapFrame(const int vertical,const int side) {
	int k,c;
	for (int i = 0; i < side + 1; i++) {
		k = 300 + 40 * i;
		c = 40 * vertical;
		//1
		Line(k, 30, k, c + 30).draw(5);
		//2
		Line(k + 800, 30, k + 800, c + 30).draw(5);
	}

	for (int i = 0; i < vertical + 1; i++) {
		k = 40 * (i + 1);
		c = 40 * side;
		//1
		Line(300, k-10, c + 300, k-10).draw(5);
		//2
		Line(1100, k-10, c + 1100, k-10).draw(5);
	}
}

//ColorMap1
void CreateMap::createMapState1(const int state,const int x,const int y){
	Rect rect(300+40*(x-1),30+40*(y-1),40,40);
	Map* map;
	map = map->getMap();
	if (state == map->ourTeamID) {
		rect.draw(Palette::Blue);
	}
	else if (state == map->otherTeamID) {
		rect.draw(Palette::Red);
	}
	else {
		rect.draw(Palette::Black);
	}
}

//ColorMap2
void CreateMap::createMapState2(const int state, const int x, const int y) {
	Rect rect(1100 + 40 * (x - 1), 30 + 40 * (y - 1), 40, 40);
	Map* map;
	map = map->getMap();
	if (state == map->ourTeamID) {
		rect.draw(Palette::Blue);
	}else if(state==map->otherTeamID){
		rect.draw(Palette::Red);
	}else{
		rect.draw(Palette::Black);
	}
}

//AgentsMap1
void CreateMap::createMapAgent1(const int who, const int x, const int y) {
	Circle circle(300 + 40 * (y - 1) + 20, 30 + 40 * (x - 1) + 20,15);
	switch (who) {
	case 1:
		circle.draw(Palette::Lightskyblue);
		break;
	case 2:
		circle.draw(Palette::Pink);
		break;
	}
}

//AgentsMap2
void CreateMap::createMapAgent2(const int who, const int x, const int y) {
	Circle circle(1100 + 40 * (y - 1) + 20, 30 + 40 * (x - 1) + 20, 15);
	switch (who) {
	case 1:
		circle.draw(Palette::Lightskyblue);
		break;
	case 2:
		circle.draw(Palette::Pink);
		break;
	}
}

//PointMap1
void CreateMap::createMapPoint1(const int point, const int x, const int y) {
	if (point >= 0) {
		font(point).draw(300 + 40 * (x - 1) + 12, 30 + 40 * (y - 1) - 2, Palette::White);
	}else{
		font(point).draw(300 + 40 * (x - 1) + 4, 30 + 40 * (y - 1) - 2, Palette::White);
	}
}

//PointMap2
void CreateMap::createMapPoint2(const int point, const int x, const int y) {
	if (point >= 0) {
		font(point).draw(1100 + 40 * (x - 1) + 12, 30 + 40 * (y - 1) - 2, Palette::White);
	}else{
		font(point).draw(1100 + 40 * (x - 1) + 4, 30 + 40 * (y - 1) - 2, Palette::White);
	}
}

//LineMap1
void CreateMap::createMapLine1(const int x1, const int y1, const int x2, const int y2) {
	Line(300 + 40 * (x1 - 1) + 20, 30 + 40 * (y1 - 1) + 20, 300 + 40 * (x2 - 1) + 20, 30 + 40 * (y2 - 1) + 20).draw(5,Palette::Black);
}

//LineMap2
void CreateMap::createMapLine2(const int x1, const int y1, const int x2, const int y2) {
	Line(1100 + 40 * (x1 - 1) + 20, 30 + 40 * (y1 - 1) + 20, 1100 + 40 * (x2 - 1) + 20, 30 + 40 * (y2 - 1) + 20).draw(5, Palette::Black);
}


bool CreateMap::createMapClass() {

	//if(json flg==false){	return false;}

	Map* map;
	map = map->getMap();


	//全てのデータファイルの初期化
	map->score.resize(2, vector<int>(3, 0));
	map->turn = 0;
	//先読みターン数の初期化
	map->readTurn = 3;

	map->isGameStarted = false;


	Agents* agents;
	agents = agents->getAgents();
	AgentsAction* agentsAcn;
	agentsAcn = agentsAcn->getAgentsAction();

	agentsAcn->actionDxDy.resize(8, vector<pair<int, pair<int,int>>>(map->readTurn+1));


	//debug用
	debugSetUp();
	createTurnField();
	return true;
}


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
	//agentsAcn->actionDxDy.resize(agentS, vector<pair<int, pair<int, int>>>(map->readTurn+1 , pair<int, pair<int, int>>(0, pair<int, int>(0, 0))));

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



//ここから下からデバッグ用関数たち
void CreateMap::debugSetUp() {
	
	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	AgentsAction* agentsAcn;
	agentsAcn = agentsAcn->getAgentsAction();
	Field* field;
	field = field->getField();
	//Map.h
	map->vertical = 10;
	map->width = 10;
	map->makeReadTurnMap = false;
	map->ourTeamID = 1;
	map->otherTeamID = 2;
	//Agents.h
	agents->ourAgents.resize(4, vector<int>(3));
	agents->otherAgents.resize(4, vector<int>(3));
	


	for (int agentnum = 10; agentnum < 10 + agents->ourAgents.size(); agentnum++) {
		int i = agentnum - 10;
		agents->ourAgents[i][0] = agentnum;
	}
	for (int agentnum = 10 + agents->ourAgents.size(); agentnum < agents->ourAgents.size() * 2; agentnum++) {
		int i = agentnum - 10 + agents->ourAgents.size();
		agents->otherAgents[i][0] = agentnum;
	}
	
	//手動でagentの初期位置入力
	agents->ourAgents[0][1] = 1;
	agents->ourAgents[0][2] = 2;
	agents->ourAgents[1][1] = 9;
	agents->ourAgents[1][2] = 1;
	agents->ourAgents[2][1] = 10;
	agents->ourAgents[2][2] = 9;
	agents->ourAgents[3][1] = 2;
	agents->ourAgents[3][2] = 10;
	
	agents->otherAgents[0][1] = 2;
	agents->otherAgents[0][2] = 1;

	agents->otherAgents[1][1] = 10;
	agents->otherAgents[1][2] = 2;

	agents->otherAgents[2][1] = 9;
	agents->otherAgents[2][2] = 10;
	
	agents->otherAgents[3][1] = 1;
	agents->otherAgents[3][2] = 9;
	
	
	//Field.h
	field->points.resize(map->width, vector<int>(map->vertical, 0));
	field->points = {
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0},
		{0,1,2,3,4,-4,-3,-2,-1,0}
	};
	
	field->tiled.resize(map->width, vector<int>(map->vertical, 0));
	field->tiled = {
		{0,2,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,2},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,1},
		{0,1,0,0,0,0,0,0,2,0}
	};

	
	field->turnTiled.resize(map->readTurn+1 ,vector<vector<int>>(map->width, vector<int>(map->vertical, 0)));
	
	rep(i, map->readTurn+1) {
		field->turnTiled[i] = field->tiled;
	}
	//for()

	
	

}
