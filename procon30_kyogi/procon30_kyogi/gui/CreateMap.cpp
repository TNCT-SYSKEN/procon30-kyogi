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
		//3
		//Line(k - 550, 560, k - 550, c + 560).draw(5);
		//4
		//Line(k, 560, k, c + 560).draw(5);
		//5
		//Line(k + 550, 560, k + 550, c + 560).draw(5);
	}

	for (int i = 0; i < vertical + 1; i++) {
		k = 40 * (i + 1);
		c = 40 * side;
		//1
		Line(300, k-10, c + 300, k-10).draw(5);
		//2
		Line(1100, k-10, c + 1100, k-10).draw(5);
		//3
		//Line(50, k + 530, c + 50, k + 530).draw(5);
		//4
		//Line(600, k + 530, c + 600, k + 530).draw(5);
		//5
		//Line(1150, k + 530, c + 1150, k + 530).draw(5);
	}
}

//ColorMap1
void CreateMap::createMapState1(const int state,const int x,const int y){
	Rect rect(300+40*(x-1),30+40*(y-1),40,40);
	switch (state) {
	case 1:
		rect.draw(Palette::Blue);
		break;
	case 2:
		rect.draw(Palette::Red);
		break;
	case 3:
		rect.draw(Palette::Black);
		break;
	}
}

//ColorMap1
void CreateMap::createMapState2(const int state, const int x, const int y) {
	Rect rect(1100 + 40 * (x - 1), 30 + 40 * (y - 1), 40, 40);
	switch (state) {
	case 1:
		rect.draw(Palette::Blue);
		break;
	case 2:
		rect.draw(Palette::Red);
		break;
	case 3:
		rect.draw(Palette::Black);
		break;
	}
}

//AgentsMap1
void CreateMap::createMapAgent1(const int who, const int x, const int y) {
	Circle circle(300 + 40 * (x - 1) + 20, 30 + 40 * (y - 1) + 20,15);
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
	Circle circle(1100 + 40 * (x - 1) + 20, 30 + 40 * (y - 1) + 20, 15);
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
	
}

//PointMap2
void CreateMap::createMapPoint2(const int point, const int x, const int y) {

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

	agents->ourAgents.resize(3, vector<int>(2, 0));
	agents->ourAgents[0][0] = 1;

	return true;
}


	//デバッグ用関数
	//debugSetUp();

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



	//for()

	
	

}
