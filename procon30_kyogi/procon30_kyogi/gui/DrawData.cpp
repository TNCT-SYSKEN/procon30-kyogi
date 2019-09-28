#include "DrawData.h"

DrawData::DrawData() 
	: gui(GUIStyle::Default) {


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
	gui.add(L"bt2", GUIButton::Create(L"リセット"));

	//JsonFile読み込み
	gui.addln(L"bt5", GUIButton::Create(L"JsonFile読み込み"));

	//先読みターン数変更
	gui.add(L"text0", GUIText::Create(L"先読みターン数"));
	gui.add(L"ptnc", GUITextArea::Create(3));
	gui.add(L"bt3", GUIButton::Create(L"OK"));

	//水平線
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//ポイント
	//水平線
	gui.add(GUIText::Create(L"Point"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//青Ourタイルポイント
	gui.add(L"text1", GUIText::Create(L"自タイル　:"));
	gui.text(L"text1").style.color = Palette::Blue;
	gui.add(L"OurTileScore", GUITextArea::Create(1, 5));

	//赤otherタイルポイント
	gui.add(L"text2", GUIText::Create(L"敵タイル　:"));
	gui.text(L"text2").style.color = Palette::Red;
	gui.addln(L"OtherTileScore", GUITextArea::Create(1, 5));

	//青our領域ポイント
	gui.add(L"text3", GUIText::Create(L"自領域　　:"));
	gui.text(L"text3").style.color = Palette::Blue;
	gui.add(L"OurAreaScore", GUITextArea::Create(1, 5));

	//赤other領域ポイント
	gui.add(L"text4", GUIText::Create(L"敵領域　　:"));
	gui.text(L"text4").style.color = Palette::Red;
	gui.addln(L"OtherAreaScore", GUITextArea::Create(1, 5));

	//青Our合計ポイント
	gui.add(L"text5", GUIText::Create(L"自合計　　:"));
	gui.text(L"text5").style.color = Palette::Blue;
	gui.add(L"OurSumScore", GUITextArea::Create(1, 5));

	//赤other合計ポイント
	gui.add(L"text6", GUIText::Create(L"敵合計　　:"));
	gui.text(L"text6").style.color = Palette::Red;
	gui.addln(L"OtherSumScore", GUITextArea::Create(1, 5));

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
	gui.add(L"turn", GUITextArea::Create(1, 5));

	//タイマー
	gui.add(L"text8", GUIText::Create(L"タイマー　:"));
	gui.addln(L"timer", GUITextArea::Create(1, 5));

	//チームID
	//青
	gui.add(L"text9", GUIText::Create(L"青ID        :"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.add(L"blueID", GUIText::Create(L""));

	//赤
	gui.add(L"text10", GUIText::Create(L"赤ID          :"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUIText::Create(L""));
	//ID入力ボタン
	gui.add(L"bt4", GUIButton::Create(L"ID入力"));
}


void DrawData::drawDataManager() {

	drawTiledScore();
	drawAreaScore();
	drawSumScore();
	clickedButton();
	drawData();
}

void DrawData::drawTiledScore() {
	Map* map;
	map = map->getMap();
	String OurTileScore;
	String OtherTileScore;

	OurTileScore = Widen(to_string(map->score[0][1]));
	OtherTileScore = Widen(to_string(map->score[1][1]));

	gui.textArea(L"OurTileScore").setText(OurTileScore);
	gui.textArea(L"OtherTileScore").setText(OtherTileScore);
	
}

void DrawData::drawAreaScore() {
	Map* map;
	map = map->getMap();

	String OurAreaScore = Widen(to_string(map->score[0][2]));
	String OtherAreaScore = Widen(to_string(map->score[1][2]));

	gui.textArea(L"OurAreaScore").setText(OurAreaScore);
	gui.textArea(L"OtherAreaScore").setText(OtherAreaScore);
}

void DrawData::drawSumScore() {
	Map* map;
	map = map->getMap();

	String OurSumScore = Widen(to_string(map->score[0][0]));
	String OtherSumScore = Widen(to_string(map->score[1][0]));

	gui.textArea(L"OurAreaScore").setText(OurSumScore);
	gui.textArea(L"OtherAreaScore").setText(OtherSumScore);
}

//ボタン入力をまとめた関数
void DrawData::clickedButton() {

	const Size targetSize(1920, 1080);
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
		inputID();
	}
	//JsonFileの読み込み
	if (gui.button(L"bt5").pushed) {

	}

	if (Input::KeyW.clicked)
	{
		// ウィンドウモード
		if (!Window::SetFullscreen(false, targetSize))
		{
			System::Exit();
		}
	}
}


void DrawData::drawData()
{
	CreateMap map;

	gui.style.showTitle = true;
	const Font font(30);
	
	//mapマスの数_JsonFileから取得
	int vertical = 3, side = 2;

	map.createMapFrame(vertical, side);


	Circle(Mouse::Pos(), 100).draw();

	font(Mouse::Pos()).draw();
	
}

void DrawData::inputID() {
	GUI guiID(GUIStyle::Default);
	const Font font(30);
	guiID.add(L"blue", GUIText::Create(L"青ID"));
	guiID.text(L"blue").style.color = Palette::Blue;
	guiID.addln(L"blueID", GUITextArea::Create(1, 5));
	guiID.add(L"red", GUIText::Create(L"赤ID"));
	guiID.text(L"red").style.color = Palette::Red;
	guiID.add(L"redID", GUITextArea::Create(1, 5));
	guiID.add(L"IDbutton", GUIButton::Create(L"決定"));
	guiID.setCenter(Window::Center());
	while (System::Update()) {
		if (guiID.button(L"IDbutton").pushed) {
			break;
		}
	}
}


