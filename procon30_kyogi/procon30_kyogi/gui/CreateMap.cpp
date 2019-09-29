#include<iostream>
#include<Siv3D.hpp>
#include"CreateMap.h"
void CreateMap::createMapFrame(const int vertical,const int side) {
	int k,c;
	for (int i = 0; i < side + 1; i++) {
		k = 300 + 40 * i;
		c = 40 * vertical;
		//1
		Line(k, 30, k, c + 30).draw(5);
		//2
		Line(k + 800, 30, k + 800, c + 30).draw(5);
		//3
		//Line(k - 550, 560, k - 550, c + 560).draw(5);
		//4
		//Line(k, 560, k, c + 560).draw(5);
		//5
		//Line(k + 550, 560, k + 550, c + 560).draw(5);
	}

	for (int i = 0; i < vertical + 1; i++) {
		k = 40 * (i + 1);
		c = 40 * side;
		//1
		Line(300, k-10, c + 300, k-10).draw(5);
		//2
		Line(1100, k-10, c + 1100, k-10).draw(5);
		//3
		//Line(50, k + 530, c + 50, k + 530).draw(5);
		//4
		//Line(600, k + 530, c + 600, k + 530).draw(5);
		//5
		//Line(1150, k + 530, c + 1150, k + 530).draw(5);
	}
}

void CreateMap::createMapState1(const int state,const int x,const int y){
	Rect rect(300+40*(x-1),30+40*(y-1),40,40);
	switch (state) {
	case 1:
		rect.draw(Palette::Blue);
		break;
	case 2:
		rect.draw(Palette::Red);
		break;
	case 3:
		rect.draw(Palette::Black);
		break;
	}
}

void CreateMap::createMapState2(const int state, const int x, const int y) {
	Rect rect(1100 + 40 * (x - 1), 30 + 40 * (y - 1), 40, 40);
	switch (state) {
	case 1:
		rect.draw(Palette::Blue);
		break;
	case 2:
		rect.draw(Palette::Red);
		break;
	case 3:
		rect.draw(Palette::Black);
		break;
	}
}

void CreateMap::createMapAgent(const int who, const int x, const int y) {

}
