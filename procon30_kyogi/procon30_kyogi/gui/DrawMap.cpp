#include"DrawMap.h"

void DrawMap::drawMapState1() {
}

void DrawMap::drawMapState2() {

}
//Agents1p
void DrawMap::drawMapAgentsTurn1() {
	Agents* agents;
	agents = agents->getAgents();
	CreateMap create;
	for (int i = 0; i < agents->ourAgents.size(); i++) {
		create.createMapAgent1(1, agents->ourAgents[i][0],agents->ourAgents[i][1]);
		create.createMapAgent1(2, agents->otherAgents[i][0],agents->otherAgents[i][1]);
	}
}

void DrawMap::drawMapAgentsTurn2() {
	Agents* agents;
	agents = agents->getAgents();
	CreateMap create;

	for (int i = 0; i < agents->ourAgents.size(); i++) {
		create.createMapAgent2(1, agents->ourAgents[i][0], agents->ourAgents[i][1]);
		create.createMapAgent2(2, agents->otherAgents[i][0], agents->otherAgents[i][1]);
	}
}

//Agents2p
void DrawMap::drawMapAgentsTurn3() {
	Agents* agents;
	agents = agents->getAgents();
	CreateMap create;
	for (int i = 0; i < agents->ourAgents.size(); i++) {
		create.createMapAgent1(1, agents->ourAgents[i][0], agents->ourAgents[i][1]);
		create.createMapAgent1(2, agents->otherAgents[i][0], agents->otherAgents[i][1]);
	}
}

void DrawMap::drawMapAgentsTurn4() {
	Agents* agents;
	agents = agents->getAgents();
	CreateMap create;
	for (int i = 0; i < agents->ourAgents.size(); i++) {
		create.createMapAgent2(1, agents->ourAgents[i][0], agents->ourAgents[i][1]);
		create.createMapAgent2(2, agents->otherAgents[i][0], agents->otherAgents[i][1]);
	}
}

void DrawMap::drawMapPoint1() {

}

void DrawMap::drawMapPoint2() {

}