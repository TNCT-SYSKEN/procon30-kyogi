
# include <Siv3D.hpp>
#include"SystemManager.h"
#include "gui/InputOutputManager.h"
#include"gui/DrawData.h"

void Main()
{

	// Windowの設定
	Window::Resize(1920, 1080);
	const Size targetSize(1920, 1080);
	//バックグラウンドを白
	Graphics::SetBackground(Palette::Gray);
	//フルスクリーン
	if (!Window::SetFullscreen(true, targetSize))
	{
		System::Exit();
	}
	SystemManager sys;
	InputOutputManager inputOutputManager;
	DrawData drawData;
	//jsonなかったら無限ループ
	inputOutputManager.init();

	while (System::Update()) {
		//drawManager
		drawData.drawDataManager();
		inputOutputManager.inputOutputManager();
	}
}
