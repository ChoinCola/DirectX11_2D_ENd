#pragma once

#include "Game_Master/Character_Master.h"
#include "Game/Character.h"

#include "Character/Character_Demo.h"
#include "Character/Knight.h"


class Card_Demo : public Character_Master
{
public:
	Card_Demo();
	~Card_Demo();

	void Update();
	void Render();
	void Insert_Vector();

private:
	std::vector<Character*> Card_Unit;

	Character_Demo* unit1 = nullptr;
	Knight* unit2 = nullptr;
};

