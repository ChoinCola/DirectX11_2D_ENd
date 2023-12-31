#pragma once

class IGame_Master
{
protected:
	SingletonBase<MousePointer> mouse;

	SingletonBase<std::list<Character*>> Character_list;
	SingletonBase<std::list<IHPBar*>> HPBar_list;
	SingletonBase<std::list<Item*>> Item_list;

	SingletonBase<std::list<ICard_UI*>> UI_list;
	SingletonBase<std::list<Button*>> Button_list;

	SingletonBase<std::list<UI_Obejct*>> Ready_UI_list; 
};
