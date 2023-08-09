#include "Framework.h"
#include "Button.h"

Button::Button(Vector3 position, Vector3 size, std::wstring Button_Name,
	std::wstring Button_Default, std::wstring Button_Push, std::wstring Button_Mark)
{
	Button_name = Button_Name;
	Push_now = false;

	this->Button_Default = new TextureRect(position, size, 0.0f,LButton + Button_Default);
	this->Button_Push = new TextureRect(position, size, 0.0f, LButton + Button_Push);
	this->Button_Mark = new TextureRect(position, size, 0.0f, LButton + Button_Mark);

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
	Button_Default->Update();
	Button_Push->Update();
	Button_Mark->Update();
}

void Button::Update(Vector3 position)
{
	Button_Default->Update(position);
	Button_Push->Update(position);
	Button_Mark->Update(position);
}

void Button::Render()
{
	if(!Push_now) {
		Button_Default->Render();
		Button_Mark->SetPosition(Mark_Default_Position);
	}
	else {
		Button_Push->Render();
		Button_Mark->SetPosition(
		Mark_Default_Position.x,
		Mark_Default_Position.y - 2,
		Mark_Default_Position.z);
	}

	Button_Mark->Render();
}
