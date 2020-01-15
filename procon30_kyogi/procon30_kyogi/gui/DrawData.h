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
	void drawMapFrame();
	GUI gui;

	void manualDirection(const int number);



private:
	void clickedButton();
	void drawTiledScore();
	void drawAreaScore();
	void drawSumScore();
	void outputTurn();


	void tokenSetUp();

	void inputID();

};

