#include "ManualInput.h"
#include "CreateMap.h"
#include "DrawData.h"
#include "../Data/Field.h"
#include <Siv3D.hpp>
void ManualInput::mousePosition() {
	Map* map;
	map = map->getMap();
	int posx, posy;
	if (map->mapChangeTurn == 0) {
		posx = Mouse::Pos().x;
		posy = Mouse::Pos().y;
		onMap(posx, posy);
	}
}

//　そのマスにいるかどうか判定
void ManualInput::onMap(const int posx, const int posy) {
	Map* map;
	map = map->getMap();

	if ((600 <= posx && posx <= 600 + 60 * map->width) && (30 <= posy && posy <= 30 + 40 * map->vertical)) {
		onMapAgents(posx, posy);
	}
}

// agentの位置を変換
void ManualInput::onMapAgents(const int posx, const int posy) {
	Agents* agents;
	agents = agents->getAgents();
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	CreateMap create;
	DrawData drawData;
	int x, y;
	x = (posx - 600) / 60;
	y = (posy - 30) / 40;
	for (int i = 0; i < agents->ourAgents.size(); i++) {
		if (x == agents->ourAgents[i][1] && y == agents->ourAgents[i][2]) {
			if (Input::MouseL.clicked) {
				map->clickedPosx = x;
				map->clickedPosy = y;
				map->isClicked = true;
				drawData.manualDirection(i);
			}
		}
	}
}

void ManualInput::clickedMap(const int x, const int y) {
	CreateMap create;
	create.createMapState(-1, x, y);
}

