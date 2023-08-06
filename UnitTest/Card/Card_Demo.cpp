#include "stdafx.h"
#include "Card_Demo.h"

Card_Demo::Card_Demo()
{
	tr = new Character_Demo(Vector3(640, 360, 0), Vector3(100, 100, 1));
	kn = new Knight(Vector3(640, 360, 0), Vector3(100, 100, 1));
	Insert_Vector();

}

Card_Demo::~Card_Demo()
{
	SAFE_DELETE(tr);
	SAFE_DELETE(kn);
}

void Card_Demo::Update()
{
	tr->Update();
	kn->Update();
}

void Card_Demo::Render()
{
	tr->Render();
	kn->Render();
}

void Card_Demo::Insert_Vector()
{
	Character_list->Get()->push_back(tr);
	Character_list->Get()->push_back(kn);

	Item_list->Get()->push_back(tr->GetItem());
	Item_list->Get()->push_back(kn->GetItem());
}

