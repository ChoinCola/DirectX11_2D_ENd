#include "stdafx.h"
#include "Card_Demo.h"

Card_Demo::Card_Demo()
{
	Card_Unit.push_back(new Character_Demo(Vector3(640, 360, 0), Vector3(90, 100, 1)));
	Card_Unit.push_back(new Knight(Vector3(640, 500, 0), Vector3(90, 100, 1)));

	int Card_unit_count = Card_Unit.size();

	//Cardinfo = new Card_UI(
	//Vector3(640, 360, 0),
	//L"TestCard",
	//0,
	//Card_unit_count,
	//&upgrade,
	//L"TestCard\nInfo"
	//);
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
