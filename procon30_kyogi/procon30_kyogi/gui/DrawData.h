#pragma once
#include "InputOutputManager.h"
#include"../Data/Map.h"
class DrawData
{
public:
	DrawData();
	void drawDataManager();
	void drawData();
	GUI gui;

public:
	void clickedButton();
	void drawTiledScore();
	void drawAreaScore();
	void drawSumScore();
	void outputTurn();

	void inputID();
};

