#include "Map.h"

Map* Map::stayMap = nullptr;
Map* Map::getMap() {
	if (stayMap == nullptr) {
		stayMap = new Map;
	}
	return stayMap;
}