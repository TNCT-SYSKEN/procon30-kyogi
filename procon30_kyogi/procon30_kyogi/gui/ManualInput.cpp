#include "ManualInput.h"
#include<Siv3D.hpp>
void ManualInput::mousePosition(){
	int x, y;
	x = Mouse::Pos().x;
	y = Mouse::Pos().y;
	onMap(x,y);
}

void ManualInput::onMap(const int x,const int y) {
	int vertical, side;//‰¼•Ï”
	if ((300<=x&&x<=300+40*side)&&(30<=y&&y<=30+40*vertical)) {
		onMap1Agents(x,y);
	}

	if ((1100<=x&&x<=1100+40*side)&&(30<=y&&y<=30+40*vertical)) {
		onMap2Agents(x,y);
	}

}

void ManualInput::onMap1Agents(const int x,const int y){

}

void ManualInput::onMap2Agents(const int x, const int y) {

}

void ManualInput::mapStateChange(){

}