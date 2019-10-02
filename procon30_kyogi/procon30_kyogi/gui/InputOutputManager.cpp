#include "InputOutputManager.h"
#include "DrawData.h"
#include "CreateMap.h"
#include "OutputData.h"
#include "TurnManager.h"
#include <Siv3D.hpp>
#include<string>

using namespace std;

void Main()
{
	CreateMap map;
	InputOutputManager input;

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
	gui.add(L"bt2", GUIButton::Create(L"���Z�b�g"));

	//JsonFile�ǂݍ���
	gui.addln(L"bt5", GUIButton::Create(L"JsonFile�ǂݍ���"));

	//��ǂ݃^�[�����ύX
	gui.add(L"text0", GUIText::Create(L"��ǂ݃^�[����"));
	gui.add(L"ptnc", GUITextArea::Create(3));
	gui.add(L"bt3", GUIButton::Create(L"OK"));

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
	gui.add(L"blueTileScore", GUITextArea::Create(1, 5));

	//�ԃ^�C���|�C���g
	gui.add(L"text2", GUIText::Create(L"�ԃ^�C���@:"));
	gui.text(L"text2").style.color = Palette::Red;
	gui.addln(L"redTileScore", GUITextArea::Create(1, 5));

	//�̈�|�C���g
	gui.add(L"text3", GUIText::Create(L"�̈�@�@:"));
	gui.text(L"text3").style.color = Palette::Blue;
	gui.add(L"blueAreaScore", GUITextArea::Create(1, 5));

	//�ԗ̈�|�C���g
	gui.add(L"text4", GUIText::Create(L"�ԗ̈�@�@:"));
	gui.text(L"text4").style.color = Palette::Red;
	gui.addln(L"redAreaScore", GUITextArea::Create(1, 5));

	//���v�|�C���g
	gui.add(L"text5", GUIText::Create(L"���v�@�@:"));
	gui.text(L"text5").style.color = Palette::Blue;
	gui.add(L"blueSumScore", GUITextArea::Create(1, 5));

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
	gui.add(L"turn", GUITextArea::Create(1, 5));

	//�^�C�}�[
	gui.add(L"text8", GUIText::Create(L"�^�C�}�[�@:"));
	gui.addln(L"timer", GUITextArea::Create(1, 5));

	//�`�[��ID
	//��
	gui.add(L"text9", GUIText::Create(L"��ID        :"));
	gui.text(L"text9").style.color = Palette::Blue;
	gui.add(L"blueID", GUIText::Create(L""));

	//��
	gui.add(L"text10", GUIText::Create(L"��ID          :"));
	gui.text(L"text10").style.color = Palette::Red;
	gui.addln(L"redID", GUIText::Create(L""));
	//ID���̓{�^��
	gui.add(L"bt4", GUIButton::Create(L"ID����"));

	// Window�̐ݒ�
	Window::Resize(1920, 1080);
	gui.style.showTitle = true;
	const Font font(30);
	const Size targetSize(1920, 1080);
	//�o�b�N�O���E���h��
	Graphics::SetBackground(Palette::Gray);
	//�t���X�N���[��
	if (!Window::SetFullscreen(true, targetSize))
	{
		System::Exit();
	}

	//map�}�X�̐�_JsonFile����擾
	int vertical = 3, side = 2;



	while (System::Update())
	{
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

		if (Input::KeyW.clicked)
		{
			// �E�B���h�E���[�h
			if (!Window::SetFullscreen(false, targetSize))
			{
				System::Exit();
			}
		}

		Circle(Mouse::Pos(), 100).draw();

		font(Mouse::Pos()).draw();
	}
}

void InputOutputManager::inputID() {
	GUI guiID(GUIStyle::Default);
	const Font font(30);
	guiID.add(L"blue",GUIText::Create(L"��ID"));
	guiID.text(L"blue").style.color = Palette::Blue;
	guiID.addln(L"blueID", GUITextArea::Create(1, 5));
	guiID.add(L"red", GUIText::Create(L"��ID"));
	guiID.text(L"red").style.color = Palette::Red;
	guiID.add(L"redID", GUITextArea::Create(1, 5));
	guiID.add(L"IDbutton", GUIButton::Create(L"����"));
	guiID.setCenter(Window::Center());
	while (System::Update()) {
		if (guiID.button(L"IDbutton").pushed) {
			break;
		}
	}
}