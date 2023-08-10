#pragma once

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
};