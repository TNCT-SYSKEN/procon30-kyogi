
# include <Siv3D.hpp>

#include"SystemManager.h"
#include"gui/InputOutputManager.h"
SystemManager sys;
	InputOutputManager iOManager;
	
void Main()
{

	DrawData drawData;
	//jsonなかったら無限ループ
	//iOManager.init();
	Map* map;
	map = map->getMap();
	map->turnFlg = false;


	while (System::Update()) {
		//drawManager
		drawData.drawDataManager();
		sys.systemManager();
	}
}
