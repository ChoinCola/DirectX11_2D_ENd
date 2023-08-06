#include "stdafx.h"
#include "Character_Master.h"
#include "stdafx.h"

Character_Master::Character_Master()
{
	Character_list->Create();
	Item_list->Create();
}

Character_Master::~Character_Master()
{
}


void Character_Master::Update()
{

}

void Character_Master::Render()
{

}

void Character_Master::Chack_Collision()
{
	bool Chack_duplication = false;
	if(Character_list != nullptr && Item_list != nullptr)
	{
		for (auto def_C : *Character_list->Get())
		{
			for (auto def_Item : *Item_list->Get())
			{ 
				// 현재 객체의 데미지 판정이 데미지 피해적용이 발생하기 전에 발생했는가?
				if(def_C->Get_hit_calculation() != nullptr) {
					for (auto def_C_damage_list : *def_C->Get_hit_calculation())
					{
						if(def_C_damage_list == def_Item) { 
						Chack_duplication = true;
						break;
						}
					}
				}

				// 충돌 판정부
				if (BoundingBox::OBB(&def_C->Getcollision(), &def_Item->Getcollision())
					&& !(def_C->GetItem() == def_Item) // 내 소유의 아이템이 아닐 경우,
					&& !Chack_duplication) // 피해가 공격시 한번만 들어가도록.
				{
					def_C->Get_hit_calculation()->push_back(def_Item);
				}
			}
		}
	}
}
