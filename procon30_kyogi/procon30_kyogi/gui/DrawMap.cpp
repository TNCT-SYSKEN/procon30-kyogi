#include"DrawMap.h"
#include"ManualInput.h"

// FrameMap -> createMapFrame()
void DrawMap::drawMapFrame() {
	Map* map;
	map = map->getMap();
	CreateMap Cmap;

	// フィールド枠線
	Cmap.createMapFrame(map->vertical, map->width);
}


// Tield 状況 draw
//StateMap
void DrawMap::drawMapState(const int turnFieldTurn) {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap Cmap;

	if (turnFieldTurn == 0) {
		for (int i = 0; i < map->vertical; i++) {
			for (int j = 0; j < map->width; j++) {
				Cmap.createMapState(field->tiled[i][j], i, j);
			}
		}
	}
	else {
		for (int i = 0; i < map->vertical; i++) {
			for (int j = 0; j < map->width; j++) {
				Cmap.createMapState(field->tiled[i][j], i, j);
				if (field->turnTiled[turnFieldTurn][j][i] == map->ourTeamID) {
					Cmap.createMapState(field->turnTiled[turnFieldTurn][i][j], i, j);
				}
			}
		}
	}
}

//AgentsMap
void DrawMap::drawMapAgentsTurn(const int turnFieldTurn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	CreateMap create;
	if (turnFieldTurn == 0) {
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapAgent(1, agents->ourAgents[i][1], agents->ourAgents[i][2]);
			create.createMapAgent(2, agents->otherAgents[i][1], agents->otherAgents[i][2]);
		}
	}
	else {
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapAgent(2, agents->otherAgents[i][1], agents->otherAgents[i][2]);
			create.createMapAgent(1, field->turnAgent[turnFieldTurn][i].first, field->turnAgent[turnFieldTurn][i].second);
		}
	}
}

//PointMap
void DrawMap::drawMapPoint() {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	for (int i = 0; i < map->vertical; i++) {
		for (int j = 0; j < map->width; j++) {
			create.createMapPoint(field->points[i][j], i, j);
		}
	}
}

//LineMap2
void DrawMap::drawMapLine(const int turnFieldTurn) {
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	CreateMap create;
	if (turnFieldTurn == map->readTurn) {
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapLine(field->turnAgent[turnFieldTurn][i].first, field->turnAgent[turnFieldTurn][i].second, field->turnAgent[turnFieldTurn + 1][i].first, field->turnAgent[turnFieldTurn + 1][i].second);
		}
	}
	else {
		// error吐くかも -> 解決
		// turn+1のせいで範囲外アクセスするからreadTurn-1までしか扱えない
		// turn を一定以上増えないように制御した
		for (int i = 0; i < agents->ourAgents.size(); i++) {
			create.createMapLine(field->turnAgent[turnFieldTurn][i].first, field->turnAgent[turnFieldTurn][i].second, field->turnAgent[turnFieldTurn + 1][i].first, field->turnAgent[turnFieldTurn + 1][i].second);
		}
	}
}

//DrawMapManager
void DrawMap::drawMapManager(const int turnFieldTurn) {
	Map* map;
	map = map->getMap();
	drawMapState(turnFieldTurn);


	//manualInput
	ManualInput manualInput;
	// clickの範囲判定
	manualInput.mousePosition();
	
	if (map->isClicked == true) {
		// エージェント選択モード（移動方向変更可能）
		manualInput.clickedMap(map->clickedPosx, map->clickedPosy);
	}

	drawMapAgentsTurn(turnFieldTurn);
	drawMapPoint();
	// error
	drawMapLine(turnFieldTurn);
	drawMapFrame();

}


