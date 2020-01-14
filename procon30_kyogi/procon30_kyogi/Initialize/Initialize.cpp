#include"Initialize.h"

// ������
void Initialize::initialize() {
	setupMap();
	setupField();
	setupAgents();
	setupAgentsAction();
}


//Map.h
void Initialize::setupMap() {
	Map* map;
	map = map->getMap();


	map->vertical = 20;
	map->width = 20;
	map->makeReadTurnMap = false;
	map->ourTeamID = 1;
	map->otherTeamID = 2;

	// score������
	map->score.resize(2, vector<int>(3, 0));
	map->turn = 0;
	// ��ǂ݃^�[�����̏�����
	map->readTurn = 3;
	map->isGameStarted = false;
}


// Field.h
void Initialize::setupField() {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();

	// field�T�C�Y������
	field->points.resize(20, vector<int>(20, 0));
	field->tiled.resize(20, vector<int>(20, 0));
	field->turnTiled.resize(map->readTurn + 1, vector<vector<int>>(20, vector<int>(20, 0)));
	field->turnAgent.resize(map->readTurn + 1, vector<pair<int, int>>(8, pair<int, int>(2, 2)));

	// readTurn������
	//rep(i, map->readTurn + 1) {
	//	field->turnTiled[i] = field->tiled;
	//}
}


// Agents.h
void Initialize::setupAgents() {
	Agents* agents;
	agents = agents->getAgents();

	// agent8��
	agents->ourAgents.resize(8, vector<int>(3));
	agents->otherAgents.resize(8, vector<int>(3));


	// agent�̏����ʒu
	rep(i, agents->ourAgents.size()) {
		rep(xy, 2) {
			//�S�������ʒu������
			agents->ourAgents[i][xy + 1] = 1;
			agents->otherAgents[i][xy + 1] = 2;
		}
	}

	// agentNumber�@������
	for (int tmp = 0; tmp < 8; tmp++) {
		agents->ourAgents[tmp][0] = tmp;
		agents->otherAgents[tmp][0] = tmp + 8;
	}

}


void Initialize::setupAgentsAction() {
	Map* map;
	map = map->getMap();
	AgentsAction* agentsAcn;
	agentsAcn = agentsAcn->getAgentsAction();

	int agentSize = 8;
	int readTurn = map->readTurn;

	// all agentnum=0, dx,dy=0
	agentsAcn->actionDxDy.resize(agentSize, vector<pair<int, pair<int, int>>>
		(readTurn, pair<int, pair<int, int>>(0, pair<int, int>(0, 0))));


}