#include "stdafx.h"
#include "Card_Demo.h"

Card_Demo::Card_Demo()
{
	Card_Unit.push_back(new Character_Demo(Vector3(640, 360, 0), Vector3(90, 100, 1)));
	Card_Unit.push_back(new Knight(Vector3(640, 500, 0), Vector3(90, 100, 1)));

	//unit1 = new Character_Demo(Vector3(640, 360, 0), Vector3(90, 100, 1));
	//unit2 = new Knight(Vector3(640, 500, 0), Vector3(90, 100, 1));

	Insert_Vector();
}

Card_Demo::~Card_Demo()
{
	for (auto def : Card_Unit) {
		SAFE_DELETE(def);
	}
	SAFE_DELETE(unit1);
	SAFE_DELETE(unit2);
}

void Card_Demo::Update()
{
	//unit1->Update();
	//unit2->Update();
}

void Card_Demo::Render()
{
	//for (auto& def : Card_Unit) {
	//	def->Render();
	//}

	//unit1->Render();
	//unit2->Render();
}

void Card_Demo::Insert_Vector()
{
	for (auto def : Card_Unit) {
		Character_list.Get()->push_back(def);
		Item_list.Get()->push_back(def->GetItem());
	}
}

