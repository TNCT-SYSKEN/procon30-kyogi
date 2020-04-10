#include "Redefine.h"


// 先読みターンをguiで変更したときにresizeをまとめて行う関数
void Redefine::readTurnChange(int beforeReadTurn,int AfterReadTurn) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	Agents* agents;
	agents = agents->getAgents();



	// 変更前よりも大きくなる時
	if (beforeReadTurn < AfterReadTurn) {
		field->turnAgent.resize(AfterReadTurn + 1, vector<pair<int, int>>(8, pair<int, int>(0, 0)));
		field->turnTiled.resize(AfterReadTurn + 1, vector<vector<int>>(20, vector<int>(20, 0)));
		agentsAction->actionDxDy.resize(agents->ourAgents.size(), vector<pair<int, pair<int, int>>>(AfterReadTurn + 1));
	}
	else {
		field->turnAgent.resize(AfterReadTurn + 1);
		field->turnTiled.resize(AfterReadTurn + 1);
		agentsAction->actionDxDy.resize(agents->ourAgents.size());
	}

	//agentsAction dxdy の調整


	map->readTurn = AfterReadTurn;

}