#include <Siv3D.hpp>
#include"SystemManager.h"

#include"gui/InputOutputManager.h"
#include"gui/DrawMap.h"
SystemManager sys;


void Main()
{

	// 初期化
	InputOutputManager iOManager;
	iOManager.init();

	DrawData drawData;
	DrawMap drawMap;
	
	Profiler::EnableWarning(false);

	while (System::Update()) {

		// drawManager
		drawData.drawDataManager();
		// sys.systemManager();
	}
}
