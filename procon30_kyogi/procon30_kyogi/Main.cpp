﻿# include <Siv3D.hpp>
# include"../procon30_kyogi/gui/InputOutputManager.h"

#include"SystemManager.h"
#include"gui/InputOutputManager.h"
SystemManager sys;
	
	
void Main()
{
	InputOutputManager gui;
	gui.inputoutputmanager();
	
	InputOutputManager iOManager;
	
	//jsonなかったら無限ループ
	//iOManager.init();
	Map *map;
	map = map->getMap();
	map->turnFlg = false;

	iOManager.init();
	DrawData drawData;
	Profiler::EnableWarning(false);

	while (System::Update()) {
		//drawManager
		drawData.drawDataManager();
		sys.systemManager();
	}
}
