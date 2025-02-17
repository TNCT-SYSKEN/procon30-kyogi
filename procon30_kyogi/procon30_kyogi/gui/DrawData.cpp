#include "DrawData.h"
#include "DrawMap.h"
#include "../Data/AgentsAction.h"

DrawData::DrawData()
	: gui(GUIStyle::Default) {


	gui.setTitle(L"kyogi");
	gui.setPos(0, 0);


	//json読み込みのためのtokenなどの指定
	//gui.addln(L"IsDebugMode", GUIToggleSwitch::Create(L"大会モード", L"DebugMode",true));

	gui.addln(L"json_option", GUIText::Create(L"JSON_option"));

	gui.add(L"token_name", GUIText::Create(L"トークン"));
	gui.addln(L"token", GUITextArea::Create(1, 14,none,false));

	gui.add(L"port_name", GUIText::Create(L"Port"));
	gui.add(L"port", GUITextArea::Create(1, 4));

	gui.add(L"matchNumberText", GUIText::Create(L"試合ID"));
	gui.addln(L"matchNumber", GUITextArea::Create(1, 2));


	//アルゴリズム回す
	gui.add(L"CalcAlgorithm", GUIButton::Create(L"評価計算"));

	//JsonFile読み込み
	gui.addln(L"getJSON", GUIButton::Create(L"MapJSON取得"));

	// Line
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	/**********************Toggle********************/
	//領域計算ONoff
	gui.addln(L"calcArea", GUIToggleSwitch::Create(L"評価計算 弱め", L"評価計算 強め", false));


	//analys
	gui.addln(L"Analys", GUIToggleSwitch::Create(L"Analys False", L"Analys True", false));

	//Input
	//水平線
	gui.add(GUIText::Create(L"Input"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);


	/*******************ボタン*******************/
	

	//全探索モード
	//gui.addln(L"searchALL", GUIToggleSwitch::Create( L"全探索モード",L"評価関数モード",true));

	//先読みターン数変更

	gui.add(L"text0", GUIText::Create(L"先読みターン数"));
	gui.add(L"ptnc", GUITextArea::Create(1, 2));
	gui.addln(L"bt3", GUIButton::Create(L"決定"));


	//最大ターン数
	//全探索で使う
	gui.add(L"textMT", GUIText::Create(L"終了ターン数"));
	gui.add(L"readMT", GUITextArea::Create(1, 2));
	gui.addln(L"btnMT", GUIButton::Create(L"決定"));

	//チームID
	//青
	gui.add(L"text9", GUIText::Create(L"自チームID        :"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.addln(L"blueID", GUITextArea::Create(1, 3, none, false));

	//赤
	gui.add(L"text10", GUIText::Create(L"敵チームID          :"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUITextArea::Create(1, 3, none, false));
	//ID入力ボタン
	gui.addln(L"bt4", GUIButton::Create(L"ID入力"));


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
	gui.add(L"text8", GUIText::Create(L" タイマー:"));
	gui.addln(L"timer", GUITextArea::Create(1, 5));


	//ターン切り替え
	gui.add(L"bt6", GUIButton::Create(L"前ターン"));
	gui.addln(L"bt7", GUIButton::Create(L"次ターン"));
	gui.style.showTitle = true;





	// Windowの設定
	Window::Resize(1920, 1080);
	const Size targetSize(1920, 1080);
	//バックグラウンドを白
	Graphics::SetBackground(Palette::Gray);
	outputTurn();
}

//一括実行
void DrawData::drawDataManager() {
	Map* map;
	map = map->getMap();
	DrawMap drawMap;

	drawTiledScore();
	drawAreaScore();
	drawSumScore();
	
	tokenSetUp();

	clickedButton();
	drawMapFrame();
	drawMap.drawMapManager(map->mapChangeTurn);
	
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

//総合表示更新
void DrawData::drawSumScore() {
	Map* map;
	map = map->getMap();

	String OurSumScore = Widen(to_string(map->score[0][0]));
	String OtherSumScore = Widen(to_string(map->score[1][0]));

	gui.textArea(L"OurSumScore").setText(OurSumScore);
	gui.textArea(L"OtherSumScore").setText(OtherSumScore);


	//ターン数
	gui.textArea(L"turn").setText(Widen(to_string(map->turn)));
}


//ボタン入力をまとめた関数
void DrawData::clickedButton() {
	Map *map;
	map = map->getMap();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	Agents* agents;
	agents = agents->getAgents();
	JsonOption* Joption;
	Joption = Joption->getJsonOption();

	const Size targetSize(1920, 1080);
	//行動確定ボタン
	if (gui.button(L"bt1").pushed) {
		//SystemManager SysM;
		//SysM.DebugSystem();
	}

	//先読みターン数決定ボタン
	if (gui.button(L"bt3").pushed) {
		/////////////////////////////////////
		Redefine redef;
 
		//String->string->int
		//先読みターン数更新
		int afterReadTurn = Parse<int>(gui.textArea(L"ptnc").text);
		redef.readTurnChange(map->readTurn, afterReadTurn);
		
	}
	//ID入力ボタン
	if (gui.button(L"bt4").pushed) {
		inputID();
	}

	//JsonFileの読み込み
	if (gui.button(L"getJSON").pushed) {
		//gui.textArea(L"port").setText(gui.textArea(L"token").text)

		FetchJson fetchJson;
		//Fetch Setting

		


		string token = gui.textArea(L"token").text.narrow();
		string port = gui.textArea(L"port").text.narrow();
		string matchNumber = Joption->matchID;

		ParseJson parseJson;


		 
		
		
		//最初のMap取得
		if (!map->firstJson) {
			//サーバーから取ってくる
			fetchJson.fetch(token, port, matchNumber, map->turn);



			//0ターンの情報

			parseJson.parse("json/data/Map/turn0.json");
			map->turn++;

			map->firstJson = true;
		}
		else {

			fetchJson.fetch(token, port, matchNumber, map->turn);

			//string 
			parseJson.parseTurn1("json/data/Map/turn" + to_string(map->turn) + ".json");
		}
	}
	// アルゴリズム回す
	if (gui.button(L"CalcAlgorithm").pushed) {
		Action_manager AC;
		AC.Action();


		//自動
		CreateJson createJson;
		createJson.createJson();

	}
	//MaxTurn入力ボタン
	if (gui.button(L"btMT").pushed) {
		map->finalTurn = Parse<int>(gui.textArea(L"readMT").text);

	}

	//Map切り替え
	if (gui.button(L"bt6").pushed) {
		if (map->mapChangeTurn > 0) {
			map->mapChangeTurn--;
		}
	}
	if (gui.button(L"bt7").pushed) {
		//-1を追加することでvector要素範囲外アクセスerror解消 
		if (map->mapChangeTurn < map->readTurn -1) {
			map->mapChangeTurn++;
		}
	}


	if (Input::KeyW.clicked)
	{
		// ウィンドウモード
		if (!Window::SetFullscreen(false, targetSize))
		{
			System::Exit();
		}
	}
	// 
	if (gui.toggleSwitch(L"calcArea").isRight) {
		map->evalutionOptionToggle = true;
	}
	else if (gui.toggleSwitch(L"calcArea").isLeft) {
		map->evalutionOptionToggle = false;
	}

	if (gui.toggleSwitch(L"Analys").isRight && map->AnalysCalcC) {
		map->AnalysField = true;
	}
	else if (gui.toggleSwitch(L"Analys").isLeft) {
		map->AnalysField = false;
	}



}

void DrawData::outputTurn() {
	Map *map;
	map = map->getMap();

	String Turn = Widen(to_string(map->turn));
	String ReadTurn = Widen(to_string(map->readTurn));


	gui.textArea(L"turn").setText(Turn);
	gui.textArea(L"ptnc").setText(ReadTurn);
}




void DrawData::tokenSetUp() {
	JsonOption* Joption;
	Joption = Joption->getJsonOption();


	String Token = Widen(Joption->token);
	Joption->port = Parse<int>(gui.textArea(L"port").text);
	Joption->matchID = Parse<int>(gui.textArea(L"matchNumber").text);

	gui.textArea(L"token").setText(Token);
}



void DrawData::drawMapFrame()
{
	CreateMap createMap;


	const Font font(30);

	Map* map;
	map = map->getMap();

	createMap.createMapFrame(map->vertical, map->width);

	Circle(Mouse::Pos(), 20).draw();
	font(Mouse::Pos()).draw();
}

void DrawData::inputID() {
	GUI guiID(GUIStyle::Default);
	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();

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
		//自分、相手ID定義
		if (guiID.button(L"IDbutton").pushed) {

			//相手チームIDがわからないとき
			if ((guiID.textArea(L"redID").text) == Widen("")) {
				//自分チームは空でなかったら登録
				if (guiID.textArea(L"blueID").text != Widen("")) {

					map->ourTeamID = Parse<int>(guiID.textArea(L"blueID").text);
					gui.textArea(L"blueID").setText(Widen(to_string(map->ourTeamID)));
				}
				break;
			}



			//if ourTeamID != blueID || oTeamID != redID
			if (map->ourTeamID != Parse<int>(guiID.textArea(L"blueID").text)
				|| map->otherTeamID != Parse<int>(guiID.textArea(L"redID").text)) {

				//if blueID == otherTeamID && redID == ourTeamID
				if (map->ourTeamID == Parse<int>(guiID.textArea(L"redID").text)
					&& map->otherTeamID == Parse<int>(guiID.textArea(L"blueID").text)) {

					//teamID　変更（敵味方変更など）
					map->ourTeamID = Parse<int>(guiID.textArea(L"redID").text);
					map->otherTeamID = Parse<int>(guiID.textArea(L"blueID").text);

					//swap ourAgents and otherAgents (in agents.h)
					vector<vector<int>>ourAgentsStack = agents->ourAgents;
					agents->ourAgents = agents->otherAgents;
					agents->otherAgents = ourAgentsStack;

				}
				//if ourTeamID==redID || otherTeamID==blueID
				else if (map->ourTeamID == Parse<int>(guiID.textArea(L"redID").text)
					|| map->otherTeamID == Parse<int>(guiID.textArea(L"blueID").text)) {

					//teamID　変更（敵味方変更など）
					map->ourTeamID = Parse<int>(guiID.textArea(L"redID").text);
					map->otherTeamID = Parse<int>(guiID.textArea(L"blueID").text);

					//swap ourAgents and otherAgents (in agents.h)
					vector<vector<int>>ourAgentsStack = agents->ourAgents;
					agents->ourAgents = agents->otherAgents;
					agents->otherAgents = ourAgentsStack;
				}
				// if no match
				else {
					//teamID　変更（敵味方変更など）
					map->ourTeamID = Parse<int>(guiID.textArea(L"blueID").text);
					map->otherTeamID = Parse<int>(guiID.textArea(L"redID").text);
				}

			}
			//表示ID更新
			gui.textArea(L"blueID").setText(Widen(to_string(map->ourTeamID)));
			gui.textArea(L"redID").setText(Widen(to_string(map->otherTeamID)));

			break;
		}
		if (guiID.button(L"IDcancel").pushed) {
			break;
		}
	}
}

void DrawData::manualDirection(const int number) {
	GUI guiManual(GUIStyle::Default);
	Map* map;


	map = map->getMap();
	guiManual.add(L"btm1", GUIButton::Create(L"左上"));
	guiManual.add(L"btm2", GUIButton::Create(L"↑"));
	guiManual.addln(L"btm3", GUIButton::Create(L"右上"));
	guiManual.add(L"btm4", GUIButton::Create(L"←"));
	guiManual.add(L"btm5", GUIButton::Create(L" 待機  "));
	guiManual.addln(L"btm6", GUIButton::Create(L"→"));
	guiManual.add(L"btm7", GUIButton::Create(L"左下"));
	guiManual.add(L"btm8", GUIButton::Create(L"↓"));
	guiManual.addln(L"btm9", GUIButton::Create(L"右下"));
	guiManual.add(L"btm10", GUIButton::Create(L"キャンセル"));
	//はみ出たから位置変える
	//guiManual.setPos(1500,800);
	guiManual.setPos(250, 800);
	CreateJson createJson;


	DrawMap drawMap;
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	while (System::Update()) {
		drawMap.drawMapManager(0);

		//上段
		if (guiManual.button(L"btm1").pushed) {
			agentsAction->actionDxDy[number][0].second.first = -1;
			agentsAction->actionDxDy[number][0].second.second = -1;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		if (guiManual.button(L"btm2").pushed) {
			agentsAction->actionDxDy[number][0].second.first = 0;
			agentsAction->actionDxDy[number][0].second.second = -1;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		if (guiManual.button(L"btm3").pushed) {
			agentsAction->actionDxDy[number][0].second.first = 1;
			agentsAction->actionDxDy[number][0].second.second = -1;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		//中段
		if (guiManual.button(L"btm4").pushed) {
			agentsAction->actionDxDy[number][0].second.first = -1;
			agentsAction->actionDxDy[number][0].second.second = 0;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		if (guiManual.button(L"btm5").pushed) {
			agentsAction->actionDxDy[number][0].second.first = 0;
			agentsAction->actionDxDy[number][0].second.second = 0;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		if (guiManual.button(L"btm6").pushed) {
			agentsAction->actionDxDy[number][0].second.first = 1;
			agentsAction->actionDxDy[number][0].second.second = 0;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		//下段
		if (guiManual.button(L"btm7").pushed) {
			agentsAction->actionDxDy[number][0].second.first = -1;
			agentsAction->actionDxDy[number][0].second.second = 1;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		if (guiManual.button(L"btm8").pushed) {
			agentsAction->actionDxDy[number][0].second.first = 0;
			agentsAction->actionDxDy[number][0].second.second = 1;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		if (guiManual.button(L"btm9").pushed) {
			agentsAction->actionDxDy[number][0].second.first = 1;
			agentsAction->actionDxDy[number][0].second.second = 1;

			createJson.createJson();
			map->isClicked = false;
			break;
		}
		//キャンセル
		if (guiManual.button(L"btm10").pushed) {
			map->isClicked = false;
			break;
		}
	}
}

