#include "stdafx.h"
#include "Card_Demo.h"

Card_Demo::Card_Demo()
{
	Card_Unit.push_back(new Character_Demo(Vector3(640, 360, 0), Vector3(90, 100, 1)));
	Card_Unit.push_back(new Knight(Vector3(640, 500, 0), Vector3(90, 100, 1)));

	int Card_unit_count = Card_Unit.size();

	for (auto def : Card_Unit)
		alldamage += def->Getdamage();

	Cardinfo = new Card_UI(
	Vector3(640, 500, 0),
	L"abcdefghijklmnopqrstuvwxyz",
	0,
	Card_unit_count,
	&upgrade,
	L"Tsdfjjjjjj바바\n엔터를쳤다.\n스 페 이 스 바 쳤 다.",
	&alldamage
	);

	UI_list.Get()->push_back(Cardinfo);
	for (auto def : Card_Unit) {
		Character_list.Get()->push_back(def);
	}
}

Card_Demo::~Card_Demo()
{
	for (auto def : Card_Unit) {
		SAFE_DELETE(def);
	}
}

void Card_Demo::Update()
{
	//Cardinfo->Update();
}

void Card_Demo::Render()
{
	//Cardinfo->Render();
}

void Card_Demo::Insert_List(std::list<Character*> *Clist, std::list<Item*> *Itlist)
{
	for (auto def : Card_Unit) {
		Clist->push_back(def);
		Itlist->push_back(def->GetItem());
	}
}
