#include"../Data/Agents.h"
#include"../Data/Field.h"
#include"../Data/Map.h"
#include"../gui/CreateMap.h"
#pragma once
class DrawMap{
public:
	void drawMapFrame();
	void drawMapState(const int);
	void drawMapAgentsTurn(const int);
	void drawMapPoint();
	void drawMapLine(const int);
	void drawMapManager(const int);
};

