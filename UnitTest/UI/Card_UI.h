#pragma once
#include "Geomatries/TextureRect.h"

class Card_UI
{
public:
	Card_UI(Vector3* position, std::wstring* CardName, int* CardBrood, int* CardUnitCount, std::list<int>* Card_Upgrade, std::wstring* Cardstring);
	~Card_UI();

	void Render();
	void Update();

private:

	std::wstring* CardName;
	std::list<int>* Card_Upgrade;
	std::wstring* Cardstring;

	Vector3* position;

	int* CardBrood;
	int* CardUnitCount;

	std::vector<TextureRect*> Card;
};

