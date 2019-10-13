#pragma once
#include "InputOutputManager.h"
#include"../Data/Map.h"
#include"../json/ParseJson.h"
#include"../algorithm/Analysis.h"


class DrawData
{
public:
	DrawData();
	void drawDataManager();
	void drawData();
	GUI gui;

	//debug
	void check();
public:
	void clickedButton();
	void drawTiledScore();
	void drawAreaScore();
	void drawSumScore();
	void outputTurn();


	void tokenSetUp();

	void inputID();
	void manualDirection(const int number);
};

