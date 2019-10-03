
# include <Siv3D.hpp>

#include"SystemManager.h"
#include"gui/InputOutputManager.h"
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


	while (System::Update()) {
		if (!map->firstJson) {

		}

		//drawManager
		drawData.drawDataManager();
		sys.systemManager();
	}
}
