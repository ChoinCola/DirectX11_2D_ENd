#pragma once
#include "Game_Master/Game_Master.h"

class UI_Master : public Game_Master
{
public:
	UI_Master();
	~UI_Master();

	virtual void Update();
	virtual void Render();
	void Chack_Collision();
};