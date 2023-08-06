#include "stdafx.h"
#include "10_Game_Demo.h"



void Game_Demo::Init()
{
	ef = new Battle_Master();
	cd = new Card_Demo();
}

void Game_Demo::Destroy()
{


}

void Game_Demo::Update()
{
	cd->Update();
	ef->Update();
}

void Game_Demo::Render()
{
	cd->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
