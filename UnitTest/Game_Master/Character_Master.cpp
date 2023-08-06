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
				// ���� ��ü�� ������ ������ ������ ���������� �߻��ϱ� ���� �߻��ߴ°�?
				if(def_C->Get_hit_calculation() != nullptr) {
					for (auto def_C_damage_list : *def_C->Get_hit_calculation())
					{
						if(def_C_damage_list == def_Item) { 
						Chack_duplication = true;
						break;
						}
					}
				}

				// �浹 ������
				if (BoundingBox::OBB(&def_C->Getcollision(), &def_Item->Getcollision())
					&& !(def_C->GetItem() == def_Item) // �� ������ �������� �ƴ� ���,
					&& !Chack_duplication) // ���ذ� ���ݽ� �ѹ��� ������.
				{
					def_C->Get_hit_calculation()->push_back(def_Item);
				}
			}
		}
	}
}
