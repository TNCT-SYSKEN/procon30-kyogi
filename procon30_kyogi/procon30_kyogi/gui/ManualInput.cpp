#include "ManualInput.h"
#include "CreateMap.h"
#include "DrawData.h"
#include "../Data/Field.h"
#include <Siv3D.hpp>
void ManualInput::mousePosition(){
	Map* map;
	map = map->getMap();
	int posx, posy;
	if (map->mapChange == 0) {
		posx = Mouse::Pos().x;
		posy = Mouse::Pos().y;
		onMap(posx,posy);
	}
}

//デバッグ用
void ManualInput::onMap(const int posx, const int posy) {
	Map* map;
	map = map->getMap();

	if ((1100 <= posx && posx <= 1100 + 40 * map->width) && (30 <= posy && posy <= 30 + 40 * map->vertical)) {
		onMapAgents(posx,posy);
	}
}

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
	x = (posx - 1100)/40+1;
	y = (posy - 30) / 40+1;
	for (int i = 0; i < agents->ourAgents.size(); i++) {
		if (y == agents->ourAgents[i][1] && x == agents->ourAgents[i][2]) {
			if (Input::MouseL.clicked) {
				map->x = x;
				map->y = y;
				map->click = true;
				drawData.manualDirection(i);
			}
		}
	}
}

void ManualInput::clickedMap(const int x,const int y) {
	CreateMap create;
	create.createMapState2(9999, x, y);
}





/*
void ManualInput::onMap(const int x,const int y) {
	Map* map;
	map = map->getMap();

	if ((300<=x&&x<=300+40*map->width)&&(30<=y&&y<=30+40*map->vertical)) {
		onMapAgents(x,y);
	}
}

void ManualInput::onMapAgents(const int x,const int y){
	Agents* agents;
	agents = agents->getAgents();
	for (int i = 0; i < agents->ourAgents.size();i++) {
		if ((300 + 40 * (agents->ourAgents[i][0]-1)<x&&x<300+40*(agents->ourAgents[i][0]))&&((30+40*(agents->ourAgents[i][1]-1)<y)&&(y<30+40*(agents->ourAgents[i][1])))) {

		}
	}
}


void ManualInput::mapStateChange(){

}
*/