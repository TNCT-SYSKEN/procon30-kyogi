#include"CreateMap.h"
void CreateMap::createMapFrame(const int vertical,const int side) {
	int k, c;
	for (int i = 0; i < side + 1; i++) {
		k = 600 + 50 * i;
		c = 50 * vertical;
		//1
		Line(k, 30, k, c + 30).draw(5);
		//2
		Line(k + 550, 30, k + 550, c + 30).draw(5);
		//3
		Line(k - 550, 560, k - 550, c + 560).draw(5);
		//4
		Line(k, 560, k, c + 560).draw(5);
		//5
		Line(k + 550, 560, k + 550, c + 560).draw(5);
	}
	for (int i = 0; i < vertical + 1; i++) {
		k = 50 * (i + 1) - 20;
		c = 50 * side;
		//1
		Line(600, k, c + 600, k).draw(5);
		//2
		Line(1150, k, c + 1150, k).draw(5);
		//3
		Line(50, k + 530, c + 50, k + 530).draw(5);
		//4
		Line(600, k + 530, c + 600, k + 530).draw(5);
		//5
		Line(1150, k + 530, c + 1150, k + 530).draw(5);
	}
}

bool CreateMap::createMapClass() {

	//if(json flg==false){	return false;}
	//return false;

	Map* map;
	map = map->getMap();

	map->turn = 0;

	
	return true;
}