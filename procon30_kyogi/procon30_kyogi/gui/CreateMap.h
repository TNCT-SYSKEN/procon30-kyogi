#pragma once
#include"InputOutputManager.h"


class CreateMap {
public:

	void createMapFrame(const int vertical, const int side);
	void createMapState(const int state, const int x, const int y);
	void createMapAgent(const int who, const int x, const int y);
	void createMapPoint(const int point, const int x, const int y);
	void createMapLine(const int x1, const int y1, const int x2, const int y2);
	const Font font;


	//void createTurnField();
private:


};
