#include<Siv3D.hpp>
#include "GuiInput.h"

void GuiInput::inputID() {
	GUI guiID(GUIStyle::Default);
	const Font font(30);
	guiID.add(L"blue", GUIText::Create(L"ê¬ID"));
	guiID.text(L"blue").style.color = Palette::Blue;
	guiID.addln(L"blueID", GUITextArea::Create(1, 5));
	guiID.add(L"red", GUIText::Create(L"ê‘ID"));
	guiID.text(L"red").style.color = Palette::Red;
	guiID.add(L"redID", GUITextArea::Create(1, 5));
	guiID.add(L"IDbutton", GUIButton::Create(L"åàíË"));
	guiID.setCenter(Window::Center());
	while (System::Update()) {
		if (guiID.button(L"IDbutton").pushed) {
			break;
		}
	}
}