#include "Framework.h"
#include "Button.h"

Button::Button(Vector3 position, Vector3 size, std::wstring Button_Name,
	std::wstring Button_Default, std::wstring Button_Push, std::wstring Button_Mark)
{
	Button_name = Button_Name;
	Push_now = false;
	Size = size;

	this->Button_Default = new TextureRect(position, Size, 0.0f,LButton + Button_Default);
	this->Button_Push = new TextureRect(position, Size, 0.0f, LButton + Button_Push);
	this->Button_Mark = new TextureRect(position, Size, 0.0f, LButton + Button_Mark);

	Mark_Default_Position = position;
}

Button::~Button()
{
	SAFE_DELETE(Button_Default);
	SAFE_DELETE(Button_Push);
	SAFE_DELETE(Button_Mark);
}

void Button::Update()
{
	if (!Push_now) {
		Button_Mark->SetPosition(
			Mark_Default_Position.x,
			Mark_Default_Position.y + 10,
			Mark_Default_Position.z);
	}
	else {
		Button_Mark->SetPosition(Mark_Default_Position);
	}

	Button_Default->Update();
	Button_Push->Update();
	Button_Mark->Update();
}

void Button::Render()
{
	if(!Push_now) {	Button_Default->Render(); }
	else { Button_Push->Render(); 
	cout << String::ToString(L"IM! Push!") << endl;
	}
	Button_Mark->Render();
}
