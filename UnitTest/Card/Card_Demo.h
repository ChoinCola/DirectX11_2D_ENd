#pragma once

#include "Game_Master/Character_Master.h"
#include "Game/Character.h"

#include "Character/Character_Demo.h"
#include "Character/Knight.h"
#include "UI/Card_UI.h"

class Card_Demo : public Game_Master
{
public:
	Card_Demo();
	~Card_Demo();

	void Update();
	void Render();
	void Insert_List(std::list<Character*> *Clist, std::list<Item*> *Itlist);

private:

	std::vector<Character*> Card_Unit;
	
	std::list<int> upgrade;
};

