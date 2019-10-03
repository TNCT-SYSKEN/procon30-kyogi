#include"CreateMap.h"

#include"../Data/Agents.h"

void CreateMap::createMapFrame(const int vertical,const int side) {
	int k, c;
	for (int i = 0; i < side + 1; i++) {
		k = 600 + 50 * i;
		c = 50 * vertical;
		//1
		Line(k, 30, k, c + 30).draw(5);
		//2
		Line(k + 550, 30, k + 550, c + 30).draw(5);
		//3
		Line(k - 550, 560, k - 550, c + 560).draw(5);
		//4
		Line(k, 560, k, c + 560).draw(5);
		//5
		Line(k + 550, 560, k + 550, c + 560).draw(5);
	}
	for (int i = 0; i < vertical + 1; i++) {
		k = 50 * (i + 1) - 20;
		c = 50 * side;
		//1
		Line(600, k, c + 600, k).draw(5);
		//2
		Line(1150, k, c + 1150, k).draw(5);
		//3
		Line(50, k + 530, c + 50, k + 530).draw(5);
		//4
		Line(600, k + 530, c + 600, k + 530).draw(5);
		//5
		Line(1150, k + 530, c + 1150, k + 530).draw(5);
	}
}

void CreateMap::createMapClass() {

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

	//デバッグ用関数
	//debugSetUp();

}

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