#include "stdafx.h"
#include "Card_UI.h"

Card_UI::Card_UI(Vector3* position, std::wstring* CardName, int* CardBrood, int* CardUnitCount, std::list<int>* Card_Upgrade, std::wstring* Cardstring)
	:position(position), CardName(CardName),  CardBrood(CardBrood), CardUnitCount(CardUnitCount),  Card_Upgrade(Card_Upgrade), Cardstring(Cardstring)
{
	Card.push_back( new TextureRect(* // Base
	this->position,						// position
	{200,400,1},						// size
	0.0f,								// rotation
	Color(.63f,.40f,.50f,1.f)			// Color
	));
	Card.push_back(new TextureRect( // UP
		{ this->position->x,
		  this->position->y + Card[0]->GetSize().y / 2,
		  this->position->z
		},
		{ Card[0]->GetSize().x,100,1 },
		0.0f,
		LUI + L"TextBox/Side_X",		// srv
		{ 0,1 }
	));
	Card.push_back(new TextureRect( // Down
		{ this->position->x,
		  this->position->y - Card[0]->GetSize().y / 2,
		  this->position->z
		},
		{ Card[0]->GetSize().x,100,1 },
		0.0f,
		LUI + L"TextBox/Side_x",
		{ 0,0 }
	));
	Card.push_back(new TextureRect( // Left
		{ this->position->x - Card[0]->GetSize().x / 2,
		  this->position->y,
		  this->position->z
		},
		{ 100,Card[0]->GetSize().y,1 },
		0.0f,
		LUI + L"TextBox/Side_Y",
		{ 0,0 }
	));
	Card.push_back(new TextureRect( // Right
		{ this->position->x + Card[0]->GetSize().x / 2,
		  this->position->y,
		  this->position->z
		},
		{ 100,Card[0]->GetSize().y,1 },
		0.0f,
		LUI + L"TextBox/Side_Y",
		{ 1,0 }
	));
}

Card_UI::~Card_UI()
{
	for(auto def : Card)
		SAFE_DELETE(def);
}

void Card_UI::Render()
{
	for(auto def: Card)
		def->Render();
}

void Card_UI::Update()
{
	for (auto def : Card)
		def->Update();
}
