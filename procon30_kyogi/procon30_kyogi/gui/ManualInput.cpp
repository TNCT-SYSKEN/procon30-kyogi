#include "ManualInput.h"
#include<Siv3D.hpp>
void ManualInput::mousePosition(){
	int x, y;
	x = Mouse::Pos().x;
	y = Mouse::Pos().y;
	onMap(x,y);
}

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

	for (int i = 0; i < agents->otherAgents.size(); i++) {
		if ((300 + 40 * (agents->otherAgents[i][0] - 1) < x&&x < 300 + 40 * (agents->otherAgents[i][0])) && ((30 + 40 * (agents->otherAgents[i][1] - 1) < y) && (y < 30 + 40 * (agents->otherAgents[i][1])))) {

		}
	}
}


void ManualInput::mapStateChange(){

}