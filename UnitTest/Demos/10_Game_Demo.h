#pragma once

#include "Card/Card_Demo.h"
#include "Game_Master/Battle_Master.h"

class Game_Demo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	Card_Demo* cd = nullptr;
	Battle_Master* ef = nullptr;
};