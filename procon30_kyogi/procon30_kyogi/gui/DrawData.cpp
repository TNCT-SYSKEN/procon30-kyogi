#include "DrawData.h"

DrawData::DrawData() 
	: gui(GUIStyle::Default) {


	gui.setTitle(L"kyogi");
	gui.setPos(0, 0);

	//Input
	//������
	gui.add(GUIText::Create(L"Input"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//�{�^��
	//�Q�[���X�^�[�g
	gui.add(L"gameStart", GUIButton::Create(L"�Q�[���X�^�[�g�I"));

	//�s���m��
	gui.add(L"bt1", GUIButton::Create(L"����"));

	//���Z�b�g
	gui.add(L"bt2", GUIButton::Create(L"���Z�b�g"));

	//JsonFile�ǂݍ���
	gui.addln(L"bt5", GUIButton::Create(L"JsonFile�ǂݍ���"));

	//��ǂ݃^�[�����ύX
	gui.add(L"text0", GUIText::Create(L"��ǂ݃^�[����"));
	gui.add(L"ptnc", GUITextArea::Create(1,3));
	gui.add(L"bt3", GUIButton::Create(L"OK"));

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
	gui.add(L"text8", GUIText::Create(L"�^�C�}�[�@:"));
	gui.addln(L"timer", GUITextArea::Create(1, 5));

	//�`�[��ID
	//��
	gui.add(L"text9", GUIText::Create(L"���`�[��ID        :"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.add(L"blueID", GUITextArea::Create(1,3,none,false));

	//��
	gui.add(L"text10", GUIText::Create(L"�G�`�[��ID          :"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUITextArea::Create(1,3,none,false));
	//ID���̓{�^��
	gui.add(L"bt4", GUIButton::Create(L"ID����"));
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

	drawTiledScore();
	drawAreaScore();
	drawSumScore();
	clickedButton();
	drawData();

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
//�����W�\���X�V
void DrawData::drawSumScore() {
	Map* map;
	map = map->getMap();

	String OurSumScore = Widen(to_string(map->score[0][0]));
	String OtherSumScore = Widen(to_string(map->score[1][0]));

	gui.textArea(L"OurSumScore").setText(OurSumScore);
	gui.textArea(L"OtherSumScore").setText(OtherSumScore);
}

//�{�^�����͂��܂Ƃ߂��֐�
void DrawData::clickedButton() {
	Map *map;
	map = map->getMap();


	const Size targetSize(1920, 1080);
	//�s���m��{�^��
	if (gui.button(L"gameStart").pushed) {
		

		//�Q�[���X�^�[�g�I�I
		map->isGameStarted = true;
		gui.button(L"gameStart").enabled = false;
	}
	if (gui.button(L"bt1").pushed) {
		gui.add(L"bt4", GUIButton::Create(L"OK"));
	}
	//���Z�b�g�{�^��
	if (gui.button(L"bt2").pushed) {
	}
	//��ǂ݃^�[��������{�^��
	if (gui.button(L"bt3").pushed) {


		//String->string->int
		//��ǂ݃^�[�����X�V
		map->readTurn = Parse<int>(gui.textArea(L"ptnc").text);
		
		gui.textArea(L"turn").setText(Widen(to_string(map->readTurn)));
	}
	//ID���̓{�^��
	if (gui.button(L"bt4").pushed) {
		inputID();
	}
	//JsonFile�̓ǂݍ���
	if (gui.button(L"bt5").pushed) {

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
	
	//map�}�X�̐�_JsonFile����擾
	int vertical = 10, side = 10;

	map.createMapFrame(vertical, side);


	Circle(Mouse::Pos(), 100).draw();

	font(Mouse::Pos()).draw();
	
}

void DrawData::inputID() {
	GUI guiID(GUIStyle::Default);
	Map* map;
	map = map->getMap();

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
		if (guiID.button(L"IDbutton").pushed) {
			//���͓ǂݎ��{�N���X�ɏ�������
			map->ourTeamID = Parse<int>(guiID.textArea(L"blueID").text);
			map->otherTeamID = Parse<int>(guiID.textArea(L"redID").text);

			//ID�X�V
			gui.textArea(L"blueID").setText(Widen(to_string(map->ourTeamID)));
			gui.textArea(L"redID").setText(Widen(to_string(map->otherTeamID)));
			break;
		}
		if (guiID.button(L"IDcancel").pushed) {
			break;
		}
	}
}


