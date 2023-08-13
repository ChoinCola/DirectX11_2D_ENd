#include "stdafx.h"
#include "Game_Master.h"

Game_Master::Game_Master()
{
	Character_list.Create();
	Card_list.Create();
	Button_list.Create();
	UI_list.Create();
	Item_list.Create();
}

Game_Master::~Game_Master()
{
}

void Game_Master::Chack_ALL_LIST()
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
		}

		if (Button_list.Get() != nullptr && ALL_list_chack) {
			cout << String::ToString(L"Button_list") << endl;
			for (auto def : *Button_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->GetPosition()) << endl;
			}
			ALL_list_chack = false;
			cout << endl;
		}

		if (UI_list.Get() != nullptr && ALL_list_chack) {
			cout << String::ToString(L"UI_list") << endl;
			for (auto def : *UI_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->GetPosition()) << endl;
			}
			ALL_list_chack = false;
			cout << endl;
		}
		ALL_list_chack = false;
	}
}
