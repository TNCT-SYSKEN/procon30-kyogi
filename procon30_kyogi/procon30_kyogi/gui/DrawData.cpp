#include "DrawData.h"
#include "DrawMap.h"
#include "../Data/AgentsAction.h"

DrawData::DrawData() 
	: gui(GUIStyle::Default) {


	gui.setTitle(L"kyogi");
	gui.setPos(0, 0);


	//json�ǂݍ��݂̂��߂�token�Ȃǂ̎w��
	gui.addln(L"IsDebugMode", GUIToggleSwitch::Create(L"���[�h", L"DebugMode",true));

	gui.addln(L"json_option", GUIText::Create(L"JSON_option"));
	
	gui.add(L"token_name", GUIText::Create(L"�g�[�N��"));
	gui.addln(L"token", GUITextArea::Create(1, 14));
	
	gui.add(L"port_name", GUIText::Create(L"Port"));
	gui.add(L"port", GUITextArea::Create(1, 4));

	gui.add(L"matchNumberText", GUIText::Create(L"����ID"));
	gui.addln(L"matchNumber", GUITextArea::Create(1, 2));


	gui.add(L"bt1", GUIButton::Create(L"�^�[���I��"));
	
	//�A���S���Y����
	gui.add(L"CalcAlgoprithm", GUIButton::Create(L"�]���v�Z"));

	//JsonFile�ǂݍ���
	gui.addln(L"getJSON", GUIButton::Create(L"MapJSON�擾"));
	
	//json����(action)
	gui.add(L"createJsonAction", GUIButton::Create(L"�s�����o��(�s������)"));
	
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//Input
	//������
	gui.add(GUIText::Create(L"Input"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);


	//�{�^��
	//�Q�[���X�^�[�g
	gui.add(L"gameStart", GUIButton::Create(L"gameStart"));

	//�S�T�����[�h
	gui.addln(L"searchALL", GUIToggleSwitch::Create( L"�S�T�����[�h",L"�]���֐����[�h",true));

	//��ǂ݃^�[�����ύX

	gui.add(L"text0", GUIText::Create(L"��ǂ݃^�[����"));
	gui.add(L"ptnc", GUITextArea::Create(1, 2));
	gui.addln(L"bt3", GUIButton::Create(L"����"));


	//�ő�^�[����
	//�S�T���Ŏg��
	gui.add(L"textMT", GUIText::Create(L"�I���^�[����"));
	gui.add(L"readMT", GUITextArea::Create(1, 2));
	gui.addln(L"btnMT", GUIButton::Create(L"����"));
	//������
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//�|�C���g
	//������
	gui.add(GUIText::Create(L"Point"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//��Our�^�C���|�C���g
	gui.add(L"text1", GUIText::Create(L"���^�C���@:"));
	gui.text(L"text1").style.color = Palette::Blue;
	gui.add(L"OurTileScore", GUITextArea::Create(1, 5));

	//��other�^�C���|�C���g
	gui.add(L"text2", GUIText::Create(L"�G�^�C���@:"));
	gui.text(L"text2").style.color = Palette::Red;
	gui.addln(L"OtherTileScore", GUITextArea::Create(1, 5));

	//��our�̈�|�C���g
	gui.add(L"text3", GUIText::Create(L"���̈�@�@:"));
	gui.text(L"text3").style.color = Palette::Blue;
	gui.add(L"OurAreaScore", GUITextArea::Create(1, 5));

	//��other�̈�|�C���g
	gui.add(L"text4", GUIText::Create(L"�G�̈�@�@:"));
	gui.text(L"text4").style.color = Palette::Red;
	gui.addln(L"OtherAreaScore", GUITextArea::Create(1, 5));

	//��Our���v�|�C���g
	gui.add(L"text5", GUIText::Create(L"�����v�@�@:"));
	gui.text(L"text5").style.color = Palette::Blue;
	gui.add(L"OurSumScore", GUITextArea::Create(1, 5));

	//��other���v�|�C���g
	gui.add(L"text6", GUIText::Create(L"�G���v�@�@:"));
	gui.text(L"text6").style.color = Palette::Red;
	gui.addln(L"OtherSumScore", GUITextArea::Create(1, 5));

	//������
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//Information
	//������
	gui.add(GUIText::Create(L"Information"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//�^�[����
	gui.add(L"text7", GUIText::Create(L"�^�[���� �F"));
	gui.add(L"turn", GUITextArea::Create(1, 5));

	//�^�C�}�[
	gui.add(L"text8", GUIText::Create(L" �^�C�}�[:"));
	gui.addln(L"timer", GUITextArea::Create(1, 5));

	//�`�[��ID
	//��
	gui.add(L"text9", GUIText::Create(L"���`�[��ID        :"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.addln(L"blueID", GUITextArea::Create(1,3,none,false));

	//��
	gui.add(L"text10", GUIText::Create(L"�G�`�[��ID          :"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUITextArea::Create(1,3,none,false));
	//ID���̓{�^��
	gui.addln(L"bt4", GUIButton::Create(L"ID����"));
	//�^�[���؂�ւ�
	gui.add(L"bt6", GUIButton::Create(L"�O�^�[��"));
	gui.addln(L"bt7", GUIButton::Create(L"���^�[��"));
	gui.style.showTitle = true;


	


	// Window�̐ݒ�
	Window::Resize(1920, 1080);
	const Size targetSize(1920, 1080);
	//�o�b�N�O���E���h��
	Graphics::SetBackground(Palette::Gray);
	//�t���X�N���[��
	if (!Window::SetFullscreen(true, targetSize))
	{
		System::Exit();
	}	
	outputTurn();
}

//�ꊇ���s
void DrawData::drawDataManager() {
	Map* map;
	map = map->getMap();
	DrawMap drawMap;
	drawTiledScore();
	drawAreaScore();
	drawSumScore();
	clickedButton();
	drawData();
	drawMap.drawMapManager(map->mapChange);

}


//�^�C���_�\���X�V
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
//�̈�\���X�V
void DrawData::drawAreaScore() {
	Map* map;
	map = map->getMap();

	String OurAreaScore = Widen(to_string(map->score[0][2]));
	String OtherAreaScore = Widen(to_string(map->score[1][2]));

	gui.textArea(L"OurAreaScore").setText(OurAreaScore);
	gui.textArea(L"OtherAreaScore").setText(OtherAreaScore);
}
//�����\���X�V
void DrawData::drawSumScore() {
	Map* map;
	map = map->getMap();

	String OurSumScore = Widen(to_string(map->score[0][0]));
	String OtherSumScore = Widen(to_string(map->score[1][0]));

	gui.textArea(L"OurSumScore").setText(OurSumScore);
	gui.textArea(L"OtherSumScore").setText(OtherSumScore);


	//�^�[����
	gui.textArea(L"turn").setText(Widen(to_string(map->turn)));
}

//�{�^�����͂��܂Ƃ߂��֐�
void DrawData::clickedButton() {
	Map *map;
	map = map->getMap();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	Agents* agents;
	agents = agents->getAgents();


	const Size targetSize(1920, 1080);
	//�s���m��{�^��
	if (gui.button(L"bt1").pushed) {
		SystemManager SysM;
		SysM.DebugSystem();
	}

	if (gui.button(L"gameStart").pushed) {
		

		//�Q�[���X�^�[�g�I�I
		map->isGameStarted = true;
		gui.button(L"gameStart").enabled = false;
	}


	//��ǂ݃^�[��������{�^��
	if (gui.button(L"bt3").pushed) {


		//String->string->int
		//��ǂ݃^�[�����X�V
		map->readTurn = Parse<int>(gui.textArea(L"ptnc").text);
		//agentsAction dxdy �̒���
		agentsAction->actionDxDy.resize(agents->ourAgents.size(), vector<pair<int, pair<int, int>>>(map->readTurn));
	}
	//ID���̓{�^��
	if (gui.button(L"bt4").pushed) {
		inputID();
	}
	if (gui.button(L"createJsonAction").pushed) {
		CreateJson cre;
		cre.createJson();


	}
	//JsonFile�̓ǂݍ���
	if (gui.button(L"getJSON").pushed) {
		//gui.textArea(L"port").setText(gui.textArea(L"token").text)
		
		FetchJson fetchJson;
			//Fetch Setting
		string token = gui.textArea(L"token").text.narrow();
		string port = gui.textArea(L"port").text.narrow();
		string matchNumber = gui.textArea(L"matchNumber").text.narrow();

		ParseJson parseJson;

		//�ŏ���Map�擾
		if (!map->firstJson) {
			//�T�[�o�[�������Ă���
			fetchJson.fetch(token, port, matchNumber, map->turn);

			
			
			//0�^�[���̏��

			parseJson.parse("json/data/Map/turn0.json");
			map->turn++;

			map->firstJson = true;
		}
		else {

			FetchJson fetchJson;
			fetchJson.fetch(token, port, matchNumber, map->turn);

			//string 
			parseJson.parseTurn1("json/data/Map/turn" + to_string(map->turn) + ".json");
		}
	}
	if (gui.button(L"CalcAlgorithm").pushed) {
		Action_manager AC;
		AC.Action();
	}
	//MaxTurn���̓{�^��
	if (gui.button(L"btMT").pushed) {
		map->finalTurn = Parse<int>(gui.textArea(L"readMT").text);

	}
	if (gui.toggleSwitch(L"searchAll").isRight) {
		map->isSearchAll = false;
	}
	if (gui.toggleSwitch(L"searchAll").isLeft) {
		map->isSearchAll = true;
	}

	//Map�؂�ւ�
	if (gui.button(L"bt6").pushed) {
		if (map->mapChange != 0) {
			map->mapChange--;
		}
	}
	if (gui.button(L"bt7").pushed) {
		if (map->mapChange != map->readTurn) {
			map->mapChange++;
		}
	}


	if (Input::KeyW.clicked)
	{
		// �E�B���h�E���[�h
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
	guiID.add(L"blue", GUIText::Create(L"���`�[��ID"));
	guiID.text(L"blue").style.color = Palette::Blue;
	guiID.addln(L"blueID", GUITextArea::Create(1, 5));
	guiID.add(L"red", GUIText::Create(L"�ԃ`�[��ID"));
	guiID.text(L"red").style.color = Palette::Red;
	guiID.add(L"redID", GUITextArea::Create(1, 5));
	guiID.add(L"IDbutton", GUIButton::Create(L"����"));
	guiID.add(L"IDcancel", GUIButton::Create(L"�L�����Z��"));
	guiID.setCenter(Window::Center());
	while (System::Update()) {
		//�����A����ID��`
		if (guiID.button(L"IDbutton").pushed) {
			//�ŏ��̃t�B�[���h�}�b�v�����Ă�����s���Ȃ��Ɗ댯

			//if ourTeamID != blueID || otherTeamID != redID
			if (map->ourTeamID != Parse<int>(guiID.textArea(L"blueID").text)
				|| map->otherTeamID != Parse<int>(guiID.textArea(L"redID").text)) {

				//if blueID == otherTeamID && redID == ourTeamID
				if (map->ourTeamID == Parse<int>(guiID.textArea(L"redID").text)
					&& map->otherTeamID == Parse<int>(guiID.textArea(L"blueID").text)) {
					
					//teamID�@�ύX�i�G�����ύX�Ȃǁj
					map->ourTeamID = Parse<int>(guiID.textArea(L"redID").text);
					map->otherTeamID = Parse<int>(guiID.textArea(L"blueID").text);

					//swap ourAgents and otherAgents (in agents.h)
					vector<vector<int>>ourAgentsStack = agents->ourAgents;
					agents->ourAgents = agents->otherAgents;
					agents->otherAgents = ourAgentsStack;

				}
				//if ourTeamID==redID || otherTeamID==blueID
				else if(map->ourTeamID == Parse<int>(guiID.textArea(L"redID").text)
					|| map->otherTeamID == Parse<int>(guiID.textArea(L"blueID").text)){
					
					//teamID�@�ύX�i�G�����ύX�Ȃǁj
					map->ourTeamID = Parse<int>(guiID.textArea(L"redID").text);
					map->otherTeamID = Parse<int>(guiID.textArea(L"blueID").text);
					
					//swap ourAgents and otherAgents (in agents.h)
					vector<vector<int>>ourAgentsStack = agents->ourAgents;
					agents->ourAgents = agents->otherAgents;
					agents->otherAgents = ourAgentsStack;
				}
				// if no match
				else {
					//teamID�@�ύX�i�G�����ύX�Ȃǁj
					map->ourTeamID = Parse<int>(guiID.textArea(L"blueID").text);
					map->otherTeamID = Parse<int>(guiID.textArea(L"redID").text);
				}

			}
			//�\��ID�X�V
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
	guiManual.add(L"btm1", GUIButton::Create(L"����"));
	guiManual.add(L"btm2", GUIButton::Create(L"��"));
	guiManual.addln(L"btm3",GUIButton::Create(L"�E��"));
	guiManual.add(L"btm4", GUIButton::Create(L"��"));
	guiManual.add(L"btm5", GUIButton::Create(L" �ҋ@  "));
	guiManual.addln(L"btm6",GUIButton::Create(L"��"));
	guiManual.add(L"btm7", GUIButton::Create(L"����"));
	guiManual.add(L"btm8", GUIButton::Create(L"��"));
	guiManual.addln(L"btm9", GUIButton::Create(L"�E��"));
	guiManual.add(L"btm10",GUIButton::Create(L"�L�����Z��"));
	guiManual.setPos(1500,800);
	DrawMap drawMap;
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	while (System::Update()) {
		drawMap.drawMapManager(0);

		//��i
		if (guiManual.button(L"btm1").pushed) {
			agentsAction->actionDxDy[number][0].second.first=-1;
			agentsAction->actionDxDy[number][0].second.second=-1;
			map->click = false;
			break;
		}
		if (guiManual.button(L"btm2").pushed) {
			agentsAction->actionDxDy[number][0].second.first=0;
			agentsAction->actionDxDy[number][0].second.second=-1;
			map->click = false;
			break;
		}
		if (guiManual.button(L"btm3").pushed) {
			agentsAction->actionDxDy[number][0].second.first=1;
			agentsAction->actionDxDy[number][0].second.second=-1;
			map->click = false;
			break;
		}
		//���i
		if (guiManual.button(L"btm4").pushed) {
			agentsAction->actionDxDy[number][0].second.first=-1;
			agentsAction->actionDxDy[number][0].second.second=0;
			map->click = false;
			break;
		}
		if (guiManual.button(L"btm5").pushed) {
			agentsAction->actionDxDy[number][0].second.first=0;
			agentsAction->actionDxDy[number][0].second.second=0;
			map->click = false;
			break;
		}
		if (guiManual.button(L"btm6").pushed) {
			agentsAction->actionDxDy[number][0].second.first=1;
			agentsAction->actionDxDy[number][0].second.second=0;
			map->click = false;
			break;
		}
		//���i
		if (guiManual.button(L"btm7").pushed) {
			agentsAction->actionDxDy[number][0].second.first=-1;
			agentsAction->actionDxDy[number][0].second.second=1;
			map->click = false;
			break;
		}
		if (guiManual.button(L"btm8").pushed) {
			agentsAction->actionDxDy[number][0].second.first=0;
			agentsAction->actionDxDy[number][0].second.second=1;
			map->click = false;
			break;
		}
		if (guiManual.button(L"btm9").pushed) {
			agentsAction->actionDxDy[number][0].second.first=1;
			agentsAction->actionDxDy[number][0].second.second=1;
			map->click = false;
			break;
		}
		//�L�����Z��
		if(guiManual.button(L"btm10").pushed) {
			map->click = false;
			break;
		}
	}
}


void DrawData::check() {
	gui.textArea(L"token").setText(L"null");
}