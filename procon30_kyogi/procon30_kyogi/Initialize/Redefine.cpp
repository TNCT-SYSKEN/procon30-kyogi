#include "Redefine.h"


// ��ǂ݃^�[����gui�ŕύX�����Ƃ���resize���܂Ƃ߂čs���֐�
void Redefine::readTurnChange(int beforeReadTurn,int AfterReadTurn) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	Agents* agents;
	agents = agents->getAgents();



	// �ύX�O�����傫���Ȃ鎞
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

	//agentsAction dxdy �̒���


	map->readTurn = AfterReadTurn;

}