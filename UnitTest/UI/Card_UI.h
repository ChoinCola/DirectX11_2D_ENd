#pragma once
#include "ICard_UI.h"

class Card_UI : public ICard_UI
{
public:
	Card_UI(Vector3 position, std::wstring CardName, int CardBrood, int CardUnitCount, std::list<int>* Card_Upgrade, std::wstring Cardstring);
	~Card_UI();

	void Render();
	void Update();
};

