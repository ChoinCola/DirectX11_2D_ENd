#include "stdafx.h"
#include "Character_Master.h"
#include "stdafx.h"

Character_Master::Character_Master()
{
	Character_list.Create();
	Item_list.Create();
}

Character_Master::~Character_Master()
{
}


void Character_Master::Update()
{
	for (auto& def : *Character_list.Get()) {
		def->Update();
	}
	Chack_Collision();
	Chack_HP();
}

void Character_Master::Render()
{
	for (auto& def : *Character_list.Get()) {
		def->Render();
	}
}

void Character_Master::Chack_Collision()
{
	{
		static bool ALL_list_chack = true;
		if (Character_list.Get() != nullptr && ALL_list_chack) {
			cout << String::ToString(L"Character_list") << endl;
			for (auto def : *Character_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->Getcollision().GetPosition()) << endl;
			}

			cout << String::ToString(L"Item_list") << endl;
			for (auto def : *Item_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->Getcollision().GetPosition()) << endl;

			}
			ALL_list_chack = false;
		}
	}

	if (Character_list.Get() != nullptr && Item_list.Get() != nullptr)
	{
		for (auto def_C : *Character_list.Get())
		{

			for (auto def_Item : *Item_list.Get())
			{
				bool Chack_duplication = false;
				// 현재 객체의 데미지 판정이 데미지 피해적용이 발생하기 전에 발생했는가?
				if (!def_C->Get_hit_calculation().empty()) {
					for (auto def_C_damage_list : def_C->Get_hit_calculation())
					{
						if (def_C_damage_list == def_Item) {
							Chack_duplication = true;
							break;
						}
					}
				}

				// 충돌 판정부
				if (BoundingBox::OBB(&def_C->Getcollision(), &def_Item->Getcollision()) == true
					&& def_C->GetItem() != def_Item // 내 소유의 아이템이 아닐 경우,
					&& def_Item->Getphysical() != 0 // 물리량이 존재할 경우.
					&& !Chack_duplication) // 피해가 공격시 한번만 들어가도록.
				{
					cout << String::ToString(def_C->GetName()) <<
						" 와 " << String::ToString(def_Item->GetName()) <<
						" 충돌 " << endl;

					def_C->Get_hit_calculation().push_back(def_Item);
				}
			}
		}
	}
}

void Character_Master::Chack_HP()
{
	for (auto def = Character_list.Get()->begin(); def != Character_list.Get()->end();)
	{
		if ((*def)->GetHP() <= 0)
		{
			Character_list.Get()->erase(def);
		}
		else { def++; }
	}
}
