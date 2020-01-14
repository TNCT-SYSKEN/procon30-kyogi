# include <Siv3D.hpp>
# include"../procon30_kyogi/gui/InputOutputManager.h"

#include"SystemManager.h"
#include"gui/InputOutputManager.h"
#include"..//procon30_kyogi/gui/DrawMap.h"
SystemManager sys;


void Main()
{
	InputOutputManager iOManager;

	//jsonなかったら無限ループ
	//iOManager.init();
	Map *map;
	map = map->getMap();
	map->turnFlg = false;
	map->isSearchAll = false;

	iOManager.init();
	DrawData drawData;
	Profiler::EnableWarning(false);

	DrawMap drawMap;

	while (System::Update()) {

		//drawManager
		drawData.drawDataManager();
		sys.systemManager();
	}
}