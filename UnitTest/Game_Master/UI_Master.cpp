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
	for (auto& def : *Button_list.Get()) {
		if (def != nullptr)
			def->Update();
	}

	for (auto& def : *Button_list.Get()) {
		if (def != nullptr)
			def->Update();
	}
}

void UI_Master::Render()
{
	for (auto& def : *UI_list.Get()) {
		if (def != nullptr)
			def->Render();
	}

	for (auto& def : *Button_list.Get()) {
		if (def != nullptr)
			def->Render();
	}
}

void UI_Master::Chack_Collision()
{
	D3DXVECTOR3 Mposition = mouse.Get()->GetMouse()->Get()->GetPosition();

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
				def_B->GetPosition().y + def_B->GetSize().y / 2 >= Mposition.y) // AABB
			{
				mouse.Get()->SetMouseState(ON_OBJECT);
				if (mouse.Get()->GetMouse()->Get()->Down(0))
				{
					def_B->Push();
				}
				else if (!mouse.Get()->GetMouse()->Get()->Press(0) && def_B->GetPush())
				{
					def_B->Push();
				}
			}
			else if (def_B->GetPush())
			{
				def_B->Push();
			}
			else { mouse.Get()->SetMouseState(IDLE); }
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
				mouse.Get()->SetMouseState(ON_OBJECT);
				if (mouse.Get()->GetMouse()->Get()->Down(0))
				{
					def_B->SetOPEN();
				}
				else if (!mouse.Get()->GetMouse()->Get()->Press(0) && def_B->GetOPEN())
				{
					def_B->SetOPEN();
				}
			}
			else if (def_B->GetOPEN())
			{
				def_B->SetOPEN();
			}
			else { mouse.Get()->SetMouseState(IDLE); }
		}
	}
}
