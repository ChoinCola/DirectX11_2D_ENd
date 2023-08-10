#include "stdafx.h"
#include "10_Game_Demo.h"



void Game_Demo::Init()
{
	cd = new Card_Demo();
	ef = new Battle_Master();
	mp = new MousePointer(Vector3{50, 50, 0}, 1);
	ShowCursor(false);
}

void Game_Demo::Destroy()
{
}

void Game_Demo::Update()
{
	ef->Update();
	mp->Update();
}

void Game_Demo::Render()
{
	ef->Render();
	mp->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
