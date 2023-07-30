#include "stdafx.h"
#include "10_Game_Demo.h"

#include "Character/Character_Demo.h"

void Game_Demo::Init()
{
	tr = new Character_Demo(Vector3(640, 360, 0), Vector3(100, 100, 1));
}

void Game_Demo::Destroy()
{
	SAFE_DELETE(tr);
}

void Game_Demo::Update()
{
	tr->Update();
}

void Game_Demo::Render()
{
	tr->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
