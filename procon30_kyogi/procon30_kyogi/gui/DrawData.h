#pragma once
#include "InputOutputManager.h"
#include"../json/ParseJson.h"
#include"../algorithm/Analysis.h"
// token,json,matchID
#include"../json/data/JsonOption.h"



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
	// token,•\Ž¦
	void tokenSetUp();

	void inputID();

};

