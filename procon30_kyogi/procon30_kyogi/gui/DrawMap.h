#include"../Data/Agents.h"
#include"../Data/Field.h"
#include"../Data/Map.h"
#include"../gui/CreateMap.h"
#pragma once
class DrawMap{
public:
	void drawMapFrame();
	void drawMapState1(const int turn);
	void drawMapState2(const int turn);
	void drawMap1AgentsTurn(const int turn);
	void drawMap2AgentsTurn(const int turn);
	void drawMapPoint1();
	void drawMapPoint2();
	void drawMapLine1(const int turn);
	void drawMapLine2(const int turn);
	void drawMapManager(const int turn);
};

