#include "stdafx.h"
#include "HUD.h"

#include "Game/UI/ProgressBar.h"

HUD::HUD()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;
	HPBar = new ProgressBar({ 0, 0, 0 }, { 500, 500, 1 }, 0.0f, TexturePath + L"jelda.png", UI::DOWN_TO_UP);
}

HUD::~HUD()
{
	SAFE_DELETE(HPBar);
}

void HUD::Update()
{
	if (Keyboard::Get()->Down(VK_F3))
	{
		percent -= 0.1f;
		HPBar->UpdateProgressBar(percent);
	}

	HPBar->Update();
}

void HUD::Render()
{
	HPBar->Render();
}
