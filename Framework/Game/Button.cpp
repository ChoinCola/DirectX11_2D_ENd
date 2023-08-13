#include "Framework.h"
#include "Button.h"

Button::Button(Vector3 position, Vector3 size, std::wstring Button_Name,
	std::wstring Button_Default, std::wstring Button_Push, std::wstring Button_Mark)
{
	Button_name = Button_Name;
	Render_now = false;
	Push_now = false;
	UP = true;
	Size = size;

	if(Button_Default != L"NULL")
		this->Button_Default = new TextureRect(position, Size, 0.0f,LButton + Button_Default);
	if (Button_Push != L"NULL")
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
			Mark_Default_Position.y + 4,
			Mark_Default_Position.z);
			UP = false;
	}
	else {
		UP = true;
		Button_Mark->SetPosition(Mark_Default_Position);
	}

	Button_Default->Update();
	Button_Push->Update();
	Button_Mark->Update();
}

void Button::Render()
{
	if(Render_now == true) {
		if(Button_Default != nullptr && Button_Push != nullptr) {
			if(!Push_now ) { Button_Default->Render(); }
			else { Button_Push->Render(); cout << String::ToString(L"IM! Push!") << endl;}
		}
		Button_Mark->Render();
	}
}
