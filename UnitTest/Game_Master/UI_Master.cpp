#include "stdafx.h"
#include "UI_Master.h"

UI_Master::UI_Master()
	: Game_Master()
{
	mouse.Create();
	Button_list.Create();
	UI_list.Create();
}

UI_Master::~UI_Master()
{
}

void UI_Master::Update()
{
	Chack_Collision();
}

void UI_Master::Render()
{
}

void UI_Master::Chack_Collision()
{
	D3DXVECTOR3 Mposition = *mouse.Get()->GetMousePointer();

	bool BOn_Object = 0;
	bool UOn_Object = 0;

	
	if (Button_list.Get() != nullptr)
	{
		for (auto def_B : *Button_list.Get())
		{
			// 오류판정
			if (def_B == nullptr)
				continue;
					
			if (def_B->GetPosition().x - def_B->GetSize().x / 2 <= Mposition.x &&
				def_B->GetPosition().x + def_B->GetSize().x / 2 >= Mposition.x &&
				def_B->GetPosition().y - def_B->GetSize().y / 2 <= Mposition.y &&
				def_B->GetPosition().y + def_B->GetSize().y / 2 >= Mposition.y &&
				def_B->GetRender()) // AABB
			{
				if(BOn_Object == false) BOn_Object = true;
				
				if (mouse.Get()->GetMouse()->Get()->Down(0)) // 충돌상태에서 마우스가 내려간다면 눌림
				{
					def_B->Push();
				}
				else if (!mouse.Get()->GetMouse()->Get()->Press(0) && def_B->GetPush()) 
				{
					def_B->Push(); // 충돌상태에서 마우스가 내려가있지 않고, 버튼이 눌려있다면, 눌림상태 해제
				}
			}
			else if (def_B->GetPush()) def_B->Push(); // 충돌중이지 않을때 눌려있다면, 눌림상태를 해제
		}
	}

	if (UI_list.Get() != nullptr)
	{
		for (auto def_B : *UI_list.Get())
		{
			// 오류판정
			if (def_B == nullptr)
				continue;

			if (def_B->GetPosition().x - def_B->GetSize().x / 2 <= Mposition.x &&
				def_B->GetPosition().x + def_B->GetSize().x / 2 >= Mposition.x &&
				def_B->GetPosition().y - def_B->GetSize().y / 2 <= Mposition.y &&
				def_B->GetPosition().y + def_B->GetSize().y / 2 >= Mposition.y) // AABB
			{
				if (UOn_Object == false) UOn_Object = true;
				if (mouse.Get()->GetMouse()->Get()->Down(0))
				{
					def_B->SetOPEN();
					def_B->SetRenderButton();
					std::cout << "Touch_Yes!" << std::endl;
				}
			}
		}
	}
	if(UOn_Object || BOn_Object) mouse.Get()->SetMouseState(ON_OBJECT);
	else mouse.Get()->SetMouseState(IDLE);
}
