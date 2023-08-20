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
	// Press���۰� Update()�� �ѹ� ������ �ٽ� ���ƿ����� true��� false�� �ٲپ���
	// �̷ν� �츮�� Press�� Update�� ������ �ѹ����� �� �ѹ��� Press�� true�� ��ȯ���� �� �ְ� �������.
	if(Press)
		Press = false;

	// �����������, Press_b(������ ����) ���� �������� �ʾ������,
	if (Push_now && Press_b) {
		Press_b = false; // ������ ���۰� ������������ false�� ��ȯ�ع���.
		Press = true; // �׸��� Press�� �������� ó��
	}
	else if(UP){
		Press_b = true; // ������ ���۴� ��ư�� UP ó�� �Ǿ������ ���� true�� ��ȯ���ְ� ��.
	} 
	// ��, ������ �ѹ����ȸ� Press�� true�� �����ϰ�, �ι�°�̻��� Update() ������ �� ���� UP�� ó���Ǳ� ��
	// false�� ��ȯ�ϰ� ��

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