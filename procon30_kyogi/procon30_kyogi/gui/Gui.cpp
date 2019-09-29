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
	//������
	gui.add(GUIText::Create(L"Input"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//�{�^��
	//�s���m��
	gui.add(L"bt1", GUIButton::Create(L"����"));

	//���Z�b�g
	gui.addln(L"bt2", GUIButton::Create(L"���Z�b�g"));

	//JsonFile�ǂݍ���
	gui.addln(L"bt5", GUIButton::Create(L"JsonFile�ǂݍ���"));

	//��ǂ݃^�[�����ύX
	gui.addln(L"text0", GUIText::Create(L"��ǂ݃^�[����"));
	gui.add(L"ptnc", GUITextArea::Create(1,5));
	gui.addln(L"bt3", GUIButton::Create(L"OK"));

	//������
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//�|�C���g
	//������
	gui.add(GUIText::Create(L"Point"));
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	//�^�C���|�C���g
	gui.add(L"text1", GUIText::Create(L"�^�C���@:"));
	gui.text(L"text1").style.color = Palette::Blue;
	gui.addln(L"blueTileScore", GUITextArea::Create(1, 5));

	//�̈�|�C���g
	gui.add(L"text3", GUIText::Create(L"�̈�@�@:"));
	gui.text(L"text3").style.color = Palette::Blue;
	gui.addln(L"blueAreaScore", GUITextArea::Create(1, 5));

	//���v�|�C���g
	gui.add(L"text5", GUIText::Create(L"���v�@�@:"));
	gui.text(L"text5").style.color = Palette::Blue;
	gui.addln(L"blueSumScore", GUITextArea::Create(1, 5));

	//�ԃ^�C���|�C���g
	gui.add(L"text2", GUIText::Create(L"�ԃ^�C���@:"));
	gui.text(L"text2").style.color = Palette::Red;
	gui.addln(L"redTileScore", GUITextArea::Create(1, 5));

	//�ԗ̈�|�C���g
	gui.add(L"text4", GUIText::Create(L"�ԗ̈�@�@:"));
	gui.text(L"text4").style.color = Palette::Red;
	gui.addln(L"redAreaScore", GUITextArea::Create(1, 5));

	//�ԍ��v�|�C���g
	gui.add(L"text6", GUIText::Create(L"�ԍ��v�@�@:"));
	gui.text(L"text6").style.color = Palette::Red;
	gui.addln(L"redSumScore", GUITextArea::Create(1, 5));

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
	gui.addln(L"turn", GUITextArea::Create(1, 5));

	//�^�C�}�[
	gui.add(L"text8", GUIText::Create(L"�^�C�}�[ �F"));
	gui.addln(L"timer", GUITextArea::Create(1, 5));

	//�`�[��ID
	//��
	gui.add(L"text9", GUIText::Create(L"��ID�@�@:"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.addln(L"blueID", GUIText::Create(L""));

	//��
	gui.add(L"text10", GUIText::Create(L"��ID�@�@:"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUIText::Create(L""));
	//ID���̓{�^��
	gui.add(L"bt4", GUIButton::Create(L"ID����"));

	// Window�̐ݒ�
	Window::Resize(1920,1080);
	gui.style.showTitle = true;
	const Font font(30);
	const Size targetSize(1920, 1080);
	Window::SetStyle(WindowStyle::Sizeable);
	//�o�b�N�O���E���h��
	Graphics::SetBackground(Palette::Gray);

	//map�}�X�̐�_JsonFile����擾
	int vertical = 16, side = 10;

	while (System::Update())
	{
		map.createMapState1(1,2,3);
		map.createMapState2(2, 1, 2 );
		map.createMapFrame(vertical, side);
		//�s���m��{�^��
		if (gui.button(L"bt1").pushed) {
			gui.add(L"bt4", GUIButton::Create(L"OK"));
		}
		//���Z�b�g�{�^��
		if (gui.button(L"bt2").pushed) {
		}
		//��ǂ݃^�[��������{�^��
		if (gui.button(L"bt3").pushed) {
		}
		//ID���̓{�^��
		if (gui.button(L"bt4").pushed) {
			input.inputID();
		}
		//JsonFile�̓ǂݍ���
		if (gui.button(L"bt5").pushed) {

		}


		Circle(Mouse::Pos(), 10).draw();

		font(Mouse::Pos()).draw();
	}
}