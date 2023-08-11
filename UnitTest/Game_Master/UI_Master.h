#pragma once

#include "Game/Character.h"
#include "Game/Button.h"
#include "Game/Item.h"
#include "math.h"

class UI_Master
{
public:
	UI_Master();
	~UI_Master();

	virtual void Update();
	virtual void Render();
	void Chack_Collision();

protected:

	SingletonBase<MousePointer> mouse;
	SingletonBase<std::list<Button*>> Button_list;
	SingletonBase<std::list<Character*>> Character_list;

};