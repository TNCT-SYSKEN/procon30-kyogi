#pragma once
#include"InputOutputManager.h"


class CreateMap {
public:

	void createMapFrame(const int vertical, const int side);
	void createMapState1(const int state, const int x, const int y);
	void createMapState2(const int state, const int x, const int y);
	void createMapAgent1(const int who, const int x, const int y);
	void createMapAgent2(const int who, const int x, const int y);
	void createMapPoint1(const int point, const int x, const int y);
	void createMapPoint2(const int point, const int x, const int y);
	void createMapLine1(const int x1, const int y1, const int x2, const int y2);
	void createMapLine2(const int x1, const int y1, const int x2, const int y2);
	const Font font;


	//void createTurnField();
private:

};
