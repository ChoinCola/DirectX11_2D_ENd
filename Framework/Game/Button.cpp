#include "Framework.h"
#include "Button.h"

Button::Button(Vector3 position, Vector3 size, std::wstring Button_Name,
	std::wstring Button_Default, std::wstring Button_Push, std::wstring Button_Mark)
{
	Button_name = Button_Name;
	Render_now = false;
	Push_now = false;
	Press = false;
	Press_b = true;
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
	// Press버퍼가 Update()를 한번 돌리고 다시 돌아왔을때 true라면 false로 바꾸어줌
	// 이로써 우리는 Press가 Update의 시퀸스 한번마다 단 한번만 Press를 true로 반환해줄 수 있게 만들었음.
	if(Press)
		Press = false;

	// 눌려있을경우, Press_b(프레스 버퍼) 아직 진입하지 않았을경우,
	if (Push_now && Press_b) {
		Press_b = false; // 프레스 버퍼가 진입했음으로 false로 반환해버림.
		Press = true; // 그리고 Press를 눌림으로 처리
	}
	else if(UP){
		Press_b = true; // 프레스 버퍼는 버튼이 UP 처리 되었을경우 에만 true를 반환해주게 됨.
	} 
	// 즉, 시퀸스 한번동안만 Press는 true를 유지하고, 두번째이상의 Update() 시퀸스 시 에는 UP이 처리되기 전
	// false를 반환하게 됨

	if (!Push_now) {
		Button_Mark->SetPosition(
			Mark_Default_Position.x,
			Mark_Default_Position.y + 1,
			Mark_Default_Position.z);
			UP = true;
	}
	else {
		UP = false;
		Button_Mark->SetPosition(Mark_Default_Position);
	}

	Button_Default->SetPosition(Mark_Default_Position);
	Button_Push->SetPosition(Mark_Default_Position);

	Button_Default->Update();
	Button_Push->Update();
	Button_Mark->Update();
}

void Button::Render()
{
	if(Render_now == true) {
		if(Button_Default != nullptr && Button_Push != nullptr) {
			if(!Push_now ) { Button_Default->Render(); }
			else { Button_Push->Render();}
		}
		Button_Mark->Render();
	}
}