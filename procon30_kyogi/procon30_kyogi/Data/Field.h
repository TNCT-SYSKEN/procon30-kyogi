#pragma once
#include"../general.h"

class Field {
public:
	//TilePointsMap
	vector<vector<int>> points;
	//TiledPointsMap
	vector<vector<int>> tiled;

	static Field* getField();
	

private:
	static Field* field;
};