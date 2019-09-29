#include<Siv3D.hpp>
#include"Gui.h"
#include"GuiInput.h"
#include"Createmap.h"
#include<stdio.h>
void Gui::gui() {
	CreateMap map;
	GuiInput input;

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"kyogi");
	gui.setPos(0, 0);


	//Input
	//水平線
	gui.add(GUIText::Create(L"Input"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//ボタン
	//行動確定
	gui.add(L"bt1", GUIButton::Create(L"決定"));

	//リセット
	gui.addln(L"bt2", GUIButton::Create(L"リセット"));

	//JsonFile読み込み
	gui.addln(L"bt5", GUIButton::Create(L"JsonFile読み込み"));

	//先読みターン数変更
	gui.addln(L"text0", GUIText::Create(L"先読みターン数"));
	gui.add(L"ptnc", GUITextArea::Create(1,5));
	gui.addln(L"bt3", GUIButton::Create(L"OK"));

	//水平線
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//ポイント
	//水平線
	gui.add(GUIText::Create(L"Point"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//青タイルポイント
	gui.add(L"text1", GUIText::Create(L"青タイル　:"));
	gui.text(L"text1").style.color = Palette::Blue;
	gui.addln(L"blueTileScore", GUITextArea::Create(1, 5));

	//青領域ポイント
	gui.add(L"text3", GUIText::Create(L"青領域　　:"));
	gui.text(L"text3").style.color = Palette::Blue;
	gui.addln(L"blueAreaScore", GUITextArea::Create(1, 5));

	//青合計ポイント
	gui.add(L"text5", GUIText::Create(L"青合計　　:"));
	gui.text(L"text5").style.color = Palette::Blue;
	gui.addln(L"blueSumScore", GUITextArea::Create(1, 5));

	//赤タイルポイント
	gui.add(L"text2", GUIText::Create(L"赤タイル　:"));
	gui.text(L"text2").style.color = Palette::Red;
	gui.addln(L"redTileScore", GUITextArea::Create(1, 5));

	//赤領域ポイント
	gui.add(L"text4", GUIText::Create(L"赤領域　　:"));
	gui.text(L"text4").style.color = Palette::Red;
	gui.addln(L"redAreaScore", GUITextArea::Create(1, 5));

	//赤合計ポイント
	gui.add(L"text6", GUIText::Create(L"赤合計　　:"));
	gui.text(L"text6").style.color = Palette::Red;
	gui.addln(L"redSumScore", GUITextArea::Create(1, 5));

	//水平線
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//Information
	//水平線
	gui.add(GUIText::Create(L"Information"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//ターン数
	gui.add(L"text7", GUIText::Create(L"ターン数 ："));
	gui.addln(L"turn", GUITextArea::Create(1, 5));

	//タイマー
	gui.add(L"text8", GUIText::Create(L"タイマー ："));
	gui.addln(L"timer", GUITextArea::Create(1, 5));

	//チームID
	//青
	gui.add(L"text9", GUIText::Create(L"青ID　　:"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.addln(L"blueID", GUIText::Create(L""));

	//赤
	gui.add(L"text10", GUIText::Create(L"赤ID　　:"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUIText::Create(L""));
	//ID入力ボタン
	gui.add(L"bt4", GUIButton::Create(L"ID入力"));

	// Windowの設定
	Window::Resize(1920,1080);
	gui.style.showTitle = true;
	const Font font(30);
	const Size targetSize(1920, 1080);
	Window::SetStyle(WindowStyle::Sizeable);
	//バックグラウンドを白
	Graphics::SetBackground(Palette::Gray);

	//mapマスの数_JsonFileから取得
	int vertical = 16, side = 10;

	while (System::Update())
	{
		map.createMapState1(1,2,3);
		map.createMapState2(2, 1, 2 );
		map.createMapFrame(vertical, side);
		//行動確定ボタン
		if (gui.button(L"bt1").pushed) {
			gui.add(L"bt4", GUIButton::Create(L"OK"));
		}
		//リセットボタン
		if (gui.button(L"bt2").pushed) {
		}
		//先読みターン数決定ボタン
		if (gui.button(L"bt3").pushed) {
		}
		//ID入力ボタン
		if (gui.button(L"bt4").pushed) {
			input.inputID();
		}
		//JsonFileの読み込み
		if (gui.button(L"bt5").pushed) {

		}


		Circle(Mouse::Pos(), 10).draw();

		font(Mouse::Pos()).draw();
	}
}