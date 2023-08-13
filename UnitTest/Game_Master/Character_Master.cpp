#include "stdafx.h"
#include "Character_Master.h"
#include "stdafx.h"

Character_Master::Character_Master()
	: Game_Master()
{
	Character_list.Create();
	Item_list.Create();
	Card_list.Create();

	Card_list.Get()->push_back(new Card_Demo());

	for (auto& def : *Card_list.Get()) {
		if (def != nullptr)
			def->Insert_List(Character_list.Get(), Item_list.Get());
	}

}

Character_Master::~Character_Master()
{
}


void Character_Master::Update()
{
	for (auto& def : *Character_list.Get()) {
		if(def != nullptr)
			def->Update();
	}

	for (auto& def : *Card_list.Get()) {
		if (def != nullptr)
			def->Update();
	}
	Chack_Collision();
	Chack_HP();
}

void Character_Master::Render()
{
	for (auto& def : *Character_list.Get()) {
		if(def != nullptr)
			def->Render();
	}
	for (auto& def : *Card_list.Get()) {
		if (def != nullptr)
			def->Render();
	}
}

void Character_Master::Chack_Collision()
{


	if (Character_list.Get() != nullptr && Item_list.Get() != nullptr)
	{
		for (auto def_C : *Character_list.Get())
		{
			// 오류판정
			if(def_C == nullptr)
				continue;

			for (auto def_Item : *Item_list.Get())
			{
				// 오류판정
				if (def_Item == nullptr)
					continue;

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
	std::list<Character*> def_list;

	for (auto def = Character_list.Get()->begin(); def != Character_list.Get()->end(); def++)
	{
		if ((*def)->GetHP() <= 0)
		{
			def_list.push_back((*def));
		}
	}

	if(!def_list.empty()) {
		for (auto def = def_list.begin(); def != def_list.end(); def++)
		{
			Character_list.Get()->remove((*def));
		}
	}
}