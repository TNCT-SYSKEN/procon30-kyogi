#include "Map.h"

Map* Map::stayMap = nullptr;
Map* Map::getMap() {
	
	return stayMap;
}