#include "stdafx.h"
#include "Card_Demo.h"

Card_Demo::Card_Demo()
{
	Card_Unit.push_back(new Character_Demo(Vector3(640, 360, 0), Vector3(90, 100, 1)));
	Card_Unit.push_back(new Knight(Vector3(640, 500, 0), Vector3(90, 100, 1)));

	Insert_Vector();
}

Card_Demo::~Card_Demo()
{
	for (auto def : Card_Unit) {
		SAFE_DELETE(def);
	}
}

void Card_Demo::Update()
{
}

void Card_Demo::Render()
{
	
}

void Card_Demo::Insert_Vector()
{
	for (auto def : Card_Unit) {
		Character_list.Get()->push_back(def);
		Item_list.Get()->push_back(def->GetItem());
	}
}

