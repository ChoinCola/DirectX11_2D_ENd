#include "stdafx.h"
#include "UI_Master.h"

UI_Master::UI_Master()
{
	mouse.Create();
	Button_list.Create();
	Button_list.Get()->push_back(new Button(
		Vector3(200,200,0),Vector3(100,100,1),
		L"Test_Button",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Heart_pattern.png"));
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
}

void UI_Master::Render()
{
	for (auto& def : *Button_list.Get()) {
		if (def != nullptr)
			def->Render();
	}
}

void UI_Master::Chack_Collision()
{
	D3DXVECTOR3 Mposition = mouse.Get()->GetMouse()->Get()->GetPosition();
	{
		static bool ALL_list_chack = true;
		if (Button_list.Get() != nullptr && ALL_list_chack) {
			cout << String::ToString(L"Button_list") << endl;
			for (auto def : *Button_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->GetPosition()) << endl;
			}
			ALL_list_chack = false;
		}
	}

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
}
