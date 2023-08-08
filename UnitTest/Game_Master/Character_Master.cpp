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
	for (auto def = Character_list.Get()->begin(); def != Character_list.Get()->end();)
	{
		if ((*def)->GetHP() <= 0)
		{
			Character_list.Get()->erase(def);
		}
		else { def++; }
	}
}
