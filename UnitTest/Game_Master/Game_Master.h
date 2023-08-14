#pragma once

class Game_Master
{
public:
	Game_Master();
	~Game_Master();
	void Chack_ALL_LIST();

protected:
	SingletonBase<MousePointer> mouse;

	SingletonBase<std::list<Character*>> Character_list;
	SingletonBase<std::list<Item*>> Item_list;

	SingletonBase<std::list<ICard_UI*>> UI_list;
	SingletonBase<std::list<Button*>> Button_list;
};
