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
			// ��������
			if(def_C == nullptr)
				continue;

			for (auto def_Item : *Item_list.Get())
			{
				// ��������
				if (def_Item == nullptr)
					continue;

				bool Chack_duplication = false;
				// ���� ��ü�� ������ ������ ������ ���������� �߻��ϱ� ���� �߻��ߴ°�?
				if (!def_C->Get_hit_calculation().empty()) {
					for (auto def_C_damage_list : def_C->Get_hit_calculation())
					{
						if (def_C_damage_list == def_Item) {
							Chack_duplication = true;
							break;
						}
					}
				}

				// �浹 ������
				if (BoundingBox::OBB(&def_C->Getcollision(), &def_Item->Getcollision()) == true
					&& def_C->GetItem() != def_Item // �� ������ �������� �ƴ� ���,
					&& def_Item->Getphysical() != 0 // �������� ������ ���.
					&& !Chack_duplication) // ���ذ� ���ݽ� �ѹ��� ������.
				{
					cout << String::ToString(def_C->GetName()) <<
						" �� " << String::ToString(def_Item->GetName()) <<
						" �浹 " << endl;

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