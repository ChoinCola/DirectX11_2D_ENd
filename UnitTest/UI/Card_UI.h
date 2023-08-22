#pragma once
#include "ICard_UI.h"

class Card_UI : public ICard_UI, public IGame_Master
{
public:
	Card_UI(Vector3 position, std::wstring CardName, int CardBrood, int CardUnitCount, std::list<int>* Card_Upgrade, std::wstring Cardstring, int* unitalldamage);
	~Card_UI();

	void Render();
	void Update();
};

