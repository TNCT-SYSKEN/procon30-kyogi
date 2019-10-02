#include"DrawMap.h"

void DrawMap::drawMapFrame() {
	Map* map;
	map = map->getMap();
	CreateMap create;
	create.createMapFrame(map->vertical,map->width);
}

void DrawMap::drawMapState1() {
	Map* map;
	map = map->getMap();
	CreateMap create;
}

void DrawMap::drawMapState2() {

}

void DrawMap::drawMapAgents1() {
	Agents* agents;
	agents = agents->getAgents;
	CreateMap create;
	for (int i = 0; i < agents->ourAgents.size(); i++) {
		create.createMapAgent1(1, agents->ourAgents[i][0],agents->ourAgents[i][1]);
		create.createMapAgent1(2, agents->otherAgents[i][0],agents->otherAgents[i][1]);
	}
}

void DrawMap::drawMapAgents2() {
	Agents* agents;
	agents = agents->getAgents;
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