#include "DrawData.h"

DrawData::DrawData() 
	: gui(GUIStyle::Default) {


	gui.setTitle(L"kyogi");
	gui.setPos(0, 0);


	//json読み込みのためのtokenなどの指定
	gui.addln(L"json_option", GUIText::Create(L"json_option"));
	gui.add(L"token_name", GUIText::Create(L"トークン"));
	gui.addln(L"token", GUITextArea::Create(1, 10));
	gui.add(L"port_name", GUIText::Create(L"Port"));
	gui.addln(L"port", GUITextArea::Create(1, 4));
	//JsonFile読み込み
	gui.addln(L"bt5", GUIButton::Create(L"JsonFile読み込み"));

	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//Input
	//水平線
	gui.add(GUIText::Create(L"Input"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);


	//ボタン
	//ゲームスタート
	gui.add(L"gameStart", GUIButton::Create(L"gameStart"));

	//行動確定
	gui.addln(L"bt1", GUIButton::Create(L"決定"));

	//リセット
	gui.addln(L"bt2", GUIButton::Create(L"リセット"));


	//JsonFile読み込み
	gui.addln(L"bt5", GUIButton::Create(L"JsonFile読み込み"));

	//先読みターン数変更
	gui.addln(L"text0", GUIText::Create(L"先読みターン数"));
	gui.add(L"ptnc", GUITextArea::Create(1,2));
	gui.add(L"bt3", GUIButton::Create(L"OK"));

	//最大ターン数
	//全探索で使う
	gui.add(L"textMT", GUIText::Create(L"最大ターン数"));
	gui.add(L"readMT", GUITextArea::Create(1, 2));
	gui.addln(L"btnMT", GUIButton::Create(L"決定"));

	//全探索モード
	gui.add(L"searchALL", GUIToggleSwitch::Create(L"評価関数モード", L"全探索モード",false));

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
	gui.addln(L"OurTileScore", GUITextArea::Create(1, 5));

	//青our領域ポイント
	gui.add(L"text3", GUIText::Create(L"自領域　　:"));
	gui.text(L"text3").style.color = Palette::Blue;
	gui.addln(L"OurAreaScore", GUITextArea::Create(1, 5));

	//青Our合計ポイント
	gui.add(L"text5", GUIText::Create(L"自合計　　:"));
	gui.text(L"text5").style.color = Palette::Blue;
	gui.addln(L"OurSumScore", GUITextArea::Create(1, 5));

	//赤otherタイルポイント
	gui.add(L"text2", GUIText::Create(L"敵タイル　:"));
	gui.text(L"text2").style.color = Palette::Red;
	gui.addln(L"OtherTileScore", GUITextArea::Create(1, 5));

	//赤other領域ポイント
	gui.add(L"text4", GUIText::Create(L"敵領域　　:"));
	gui.text(L"text4").style.color = Palette::Red;
	gui.addln(L"OtherAreaScore", GUITextArea::Create(1, 5));
	
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
	gui.addln(L"turn", GUITextArea::Create(1, 5));

	//タイマー
	gui.add(L"text8", GUIText::Create(L"タイマー　:"));
	gui.addln(L"timer", GUITextArea::Create(1, 5));

	//チームID
	//青
	gui.add(L"text9", GUIText::Create(L"自チームID        :"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.addln(L"blueID", GUITextArea::Create(1,3,none,false));

	//赤
	gui.add(L"text10", GUIText::Create(L"敵チームID          :"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUITextArea::Create(1,3,none,false));
	//ID入力ボタン
	gui.addln(L"bt4", GUIButton::Create(L"ID入力"));
	//ターン切り替え
	gui.add(L"bt6", GUIButton::Create(L"前ターン"));
	gui.addln(L"bt7", GUIButton::Create(L"次ターン"));
	gui.style.showTitle = true;


	


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
	outputTurn();
}

//一括実行
void DrawData::drawDataManager() {

	drawTiledScore();
	drawAreaScore();
	drawSumScore();
	clickedButton();
	drawData();

}


//タイル点表示更新
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
//領域表示更新
void DrawData::drawAreaScore() {
	Map* map;
	map = map->getMap();

	String OurAreaScore = Widen(to_string(map->score[0][2]));
	String OtherAreaScore = Widen(to_string(map->score[1][2]));

	gui.textArea(L"OurAreaScore").setText(OurAreaScore);
	gui.textArea(L"OtherAreaScore").setText(OtherAreaScore);
}
//総合展表示更新
void DrawData::drawSumScore() {
	Map* map;
	map = map->getMap();

	String OurSumScore = Widen(to_string(map->score[0][0]));
	String OtherSumScore = Widen(to_string(map->score[1][0]));

	gui.textArea(L"OurSumScore").setText(OurSumScore);
	gui.textArea(L"OtherSumScore").setText(OtherSumScore);
}

//ボタン入力をまとめた関数
void DrawData::clickedButton() {
	Map *map;
	map = map->getMap();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	Agents* agents;
	agents = agents->getAgents();


	const Size targetSize(1920, 1080);
	//行動確定ボタン
	if (gui.button(L"gameStart").pushed) {
		

		//ゲームスタート！！
		map->isGameStarted = true;
		gui.button(L"gameStart").enabled = false;
	}
	if (gui.button(L"bt1").pushed) {
		gui.add(L"bt4", GUIButton::Create(L"OK"));
	}
	//リセットボタン
	if (gui.button(L"bt2").pushed) {
	}
	//先読みターン数決定ボタン
	if (gui.button(L"bt3").pushed) {


		//String->string->int
		//先読みターン数更新
		map->readTurn = Parse<int>(gui.textArea(L"ptnc").text);
		//agentsAction dxdy の調整
		agentsAction->actionDxDy.resize(agents->ourAgents.size(), vector<pair<int, pair<int, int>>>(map->readTurn));
	}
	//ID入力ボタン
	if (gui.button(L"bt4").pushed) {
		inputID();
	}
	//JsonFileの読み込み
	if (gui.button(L"bt5").pushed) {
		//gui.textArea(L"port").setText(gui.textArea(L"token").text);



	}
	//MaxTurn入力ボタン
	if (gui.button(L"btMT").pushed) {
		map->finalTurn = Parse<int>(gui.textArea(L"readMT").text);

	}
	if (gui.toggleSwitch(L"searchAll").isRight) {
		map->isSearchAll = true;
	}
	if (gui.toggleSwitch(L"searchAll").isLeft) {
		map->isSearchAll = false;
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

void DrawData::outputTurn() {
	Map *map;
	map = map->getMap();

	String Turn = Widen(to_string(map->turn));
	String Rturn = Widen(to_string(map->readTurn));


	gui.textArea(L"turn").setText(Turn);
	gui.textArea(L"ptnc").setText(Rturn);
}


void DrawData::drawData()
{
	CreateMap map;

	
	const Font font(30);
	
	Map* map1;
	map1 = map1->getMap();

	map.createMapFrame(map1->vertical,map1->width);


	Circle(Mouse::Pos(), 100).draw();

	font(Mouse::Pos()).draw();
	
}

void DrawData::inputID() {
	GUI guiID(GUIStyle::Default);
	Map* map;
	map = map->getMap();

	const Font font(30);
	guiID.add(L"blue", GUIText::Create(L"自チームID"));
	guiID.text(L"blue").style.color = Palette::Blue;
	guiID.addln(L"blueID", GUITextArea::Create(1, 5));
	guiID.add(L"red", GUIText::Create(L"赤チームID"));
	guiID.text(L"red").style.color = Palette::Red;
	guiID.add(L"redID", GUITextArea::Create(1, 5));
	guiID.add(L"IDbutton", GUIButton::Create(L"決定"));
	guiID.add(L"IDcancel", GUIButton::Create(L"キャンセル"));
	guiID.setCenter(Window::Center());
	while (System::Update()) {
		if (guiID.button(L"IDbutton").pushed) {
			//入力読み取り＋クラスに書き込み
			map->ourTeamID = Parse<int>(guiID.textArea(L"blueID").text);
			map->otherTeamID = Parse<int>(guiID.textArea(L"redID").text);

			//ID更新
			gui.textArea(L"blueID").setText(Widen(to_string(map->ourTeamID)));
			gui.textArea(L"redID").setText(Widen(to_string(map->otherTeamID)));
			
			
			break;
		}
		if (guiID.button(L"IDcancel").pushed) {
			break;
		}
	}
}


