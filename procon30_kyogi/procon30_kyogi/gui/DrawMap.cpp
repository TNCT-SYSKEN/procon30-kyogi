#include"DrawMap.h"
//debug—p
//FrameMap
void DrawMap::drawMapFrame() {
	Map* map1;
	map1 = map1->getMap();
	CreateMap map;
	map.createMapFrame(map1->vertical, map1->width);
}

//StateMap
void DrawMap::drawMapState2(const int turn) {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turn == 0) {
		for (int i = 0; i < map->vertical; i++) {
			for (int j = 0; j < map->width; j++) {
				create.createMapState2(field->tiled[i][j], i + 1, j + 1);
			}
		}
	}else{
		for (int i = 0; i < map->vertical; i++) {
			for (int j = 0; j < map->width; j++) {
				create.createMapState2(field->turnTiled[turn][i][j], i + 1, j + 1);
			}
		}
	}
}

//AgentsMap
void DrawMap::drawMap2AgentsTurn(const int turn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	CreateMap create;
	if (turn == 0) {
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapAgent2(1, field->turnAgent[turn][i].first+1,field->turnAgent[turn][i].second+1);
			create.createMapAgent2(2, agents->otherAgents[i][1], agents->otherAgents[i][2]);
		}
	}else{
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapAgent2(1, field->turnAgent[turn][i].first+1, field->turnAgent[turn][i].second+1);
		}
	}
}

//PointMap
void DrawMap::drawMapPoint2() {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	for (int i = 0; i < map->vertical; i++) {
		for (int j = 0; j < map->width; j++) {
			create.createMapPoint2(field->points[i][j], i + 1, j + 1);
		}
	}
}

//LineMap2
void DrawMap::drawMapLine2(const int turn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turn == map->readTurn) {
		//for (int i = 0; i < agents->ourAgents.size(); i++) {
			//create.createMapLine1(field->turnAgent[turn][i].first, field->turnAgent[turn][i].second, field->turnAgent[turn + 1][i].first, field->turnAgent[turn + 1][i].second);
		//}
	}else{
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapLine1(field->turnAgent[turn][i].first+1, field->turnAgent[turn][i].second+1, field->turnAgent[turn + 1][i].first+1, field->turnAgent[turn + 1][i].second+1);
		}
	}
}

//DrawMapManager
void DrawMap::drawMapManager(const int turn) {
	drawMapState2(turn);
	drawMap2AgentsTurn(turn);
	drawMapPoint2();
	drawMapLine2(turn);
	drawMapFrame();
}


/*
//FrameMap
void DrawMap::drawMapFrame() {
	Map* map1;
	map1 = map1->getMap();
	CreateMap map;
	map.createMapFrame(map1->vertical, map1->width);
}

//StateMap1
void DrawMap::drawMapState1(const int turn) {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turn == map->readTurn) {

	}else if(turn==0){
		for (int i = 0; i < map->vertical; i++) {
			for (int j = 0; j < map->width; j++) {
				create.createMapState1(field->tiled[i][j], i+1, j+1);
			}
		}
	}else {
		for (int i = 0; i < map->vertical; i++) {
			for (int j = 0; j < map->width; j++) {
				create.createMapState1(field->turnTiled[turn][i][j], i + 1, j + 1);
			}
		}
	}
}

//StateMap2
void DrawMap::drawMapState2(const int turn) {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turn == 0) {

	}else{
		for (int i = 0; i < map->vertical; i++) {
			for (int j = 0; j < map->width; j++) {
				create.createMapState2(field->turnTiled[turn][i][j], i + 1, j + 1);
			}
		}
	}
}

//AgentsMap1
void DrawMap::drawMap1AgentsTurn(const int turn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turn == map->readTurn) {
		
	}else if(turn == 0){
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapAgent1(1, field->turnAgent[turn][i].first, field->turnAgent[turn][i].second);
			create.createMapAgent1(2, agents->otherAgents[i][1], agents->otherAgents[i][2]);
		}
	}else{
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapAgent1(1,field->turnAgent[turn][i].first,field->turnAgent[turn][i].second);
		}
	}
}

//AgentsMap2
void DrawMap::drawMap2AgentsTurn(const int turn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	CreateMap create;
	if (turn == 0) {
		
	}else{
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapAgent2(1, field->turnAgent[turn][i].first, field->turnAgent[turn][i].second);
		}
	}
}

//PointMap1
void DrawMap::drawMapPoint1() {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	for (int i = 0; i < map->vertical; i++) {
		for (int j = 0; j < map->width; j++) {
			create.createMapPoint1(field->points[i][j], i + 1, j + 1);
		}
	}
}

//PointMap2
void DrawMap::drawMapPoint2() {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	for (int i = 0; i < map->vertical; i++) {
		for (int j = 0; j < map->width; j++) {
			create.createMapPoint2(field->points[i][j], i + 1, j + 1);
		}
	}
}

//LineMap1
void DrawMap::drawMapLine1(const int turn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turn == map->readTurn) {

	}else{
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapLine1(field->turnAgent[turn][i].first, field->turnAgent[turn][i].second, field->turnAgent[turn+1][i].first, field->turnAgent[turn+1][i].second);
		}
	}
}

//LineMap2
void DrawMap::drawMapLine2(const int turn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turn == map->readTurn) {
		//for (int i = 0; i < agents->ourAgents.size(); i++) {
			//create.createMapLine1(field->turnAgent[turn][i].first, field->turnAgent[turn][i].second, field->turnAgent[turn + 1][i].first, field->turnAgent[turn + 1][i].second);
		//}
	}else{
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapLine1(field->turnAgent[turn][i].first, field->turnAgent[turn][i].second, field->turnAgent[turn + 1][i].first, field->turnAgent[turn + 1][i].second);
		}
	}
}

//DrawMapManager
void DrawMap::drawMapManager(const int turn) {
	drawMapState1(turn);
	drawMapState2(turn+1);
	drawMap1AgentsTurn(turn);
	drawMap2AgentsTurn(turn+1);
	drawMapLine1(turn);
	drawMapLine2(turn+1);
	drawMapPoint1();
	drawMapPoint2();
	drawMapFrame();
}
*/