#include "stdafx.h"
#include "Game_Master.h"

template <class T>
void ExecuteIfNotNull(T* instance, void (T::*memberFunction)()) {
    if (instance != nullptr) {
        (instance->*memberFunction)();
    }
}

Game_Master::Game_Master()
{

	Character_list.Create();
	HPBar_list.Create();
	Item_list.Create();

	UI_list.Create();
	Button_list.Create();
	
	Ready_UI_list.Create();
}

Game_Master::~Game_Master()
{
}

void Game_Master::Chack_ALL_LIST()
{
	{
		if (Character_list.Get() != nullptr) {
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

		if (Button_list.Get() != nullptr) {
			cout << String::ToString(L"Button_list") << endl;
			for (auto def : *Button_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->GetPosition()) << endl;
			}
			cout << endl;
		}

		if (UI_list.Get() != nullptr) {
			cout << String::ToString(L"UI_list") << endl;
			for (auto def : *UI_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->GetPosition()) << endl;
			}
			cout << endl;
		}

		if (Ready_UI_list.Get() != nullptr) {
			cout << String::ToString(L"Ready_UI_list") << endl;
			for (auto def : *Ready_UI_list.Get()) {
				cout << String::ToString(def->GetName()) << endl;
				cout << String::ToString(def->GetPosition()) << endl;
			}
			cout << endl;
		}
	}
}

void Game_Master::Update()
{

	for(auto def : *Character_list.Get())
		def->Update();
	for (auto def : *HPBar_list.Get())
		def->Update();
	for (auto def : *Item_list.Get())
		def->Update();
	for (auto def : *UI_list.Get())
		def->Update();
	for (auto def : *Button_list.Get())
		def->Update();
	for (auto def : *Ready_UI_list.Get())
		def->Update();
	mouse.Get()->Update();
}

void Game_Master::Render()
{
	
	for (auto def : *Character_list.Get()) {
		def->Render();
		def->GetItem()->Render();
	}
	for (auto def : *HPBar_list.Get())
		def->Render();
	//for (auto def : *Item_list.Get())
	//	def->Render();
	for (auto def : *UI_list.Get()) {
		def->Render();
		}
	for (auto def : *Button_list.Get())
		def->Render();
	for (auto def : *Ready_UI_list.Get())
		def->Render();
	mouse.Get()->Render();
}

