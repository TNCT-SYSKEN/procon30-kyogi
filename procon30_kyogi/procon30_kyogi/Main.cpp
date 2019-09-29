
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

	iOManager.init();
	DrawData drawData;
	Profiler::EnableWarning(false);

	while (System::Update()) {
		//drawManager
		drawData.drawDataManager();
		sys.systemManager();
	}
}
