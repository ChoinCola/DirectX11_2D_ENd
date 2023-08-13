#pragma once

#include "Game/Character.h"
#include "Game/Item.h"

#include "Game/Button.h"
#include "UI/ICard_UI.h"
#include "Card/Card_Demo.h"

class Game_Master
{
public:
	Game_Master();
	~Game_Master();
private:
void Chack_ALL_LIST();

protected:
	SingletonBase<MousePointer> mouse;
	SingletonBase<std::list<Character*>> Character_list;
	SingletonBase<std::list<Card_Demo*>> Card_list;
	SingletonBase<std::list<Button*>> Button_list;
	SingletonBase<std::list<ICard_UI*>> UI_list;
	SingletonBase<std::list<Item*>> Item_list;
};
