#include "stdafx.h"
#include "10_Game_Demo.h"



void Game_Demo::Init()
{	
	GM = new Game_Master();
	mp = new MousePointer(Vector3{50, 50, 0});
	cd = new Card_Demo();
	UM = new UI_Master();
	CM = new Character_Master();
	ShowCursor(false);
	GM->Chack_ALL_LIST();
}

void Game_Demo::Destroy()
{
}

void Game_Demo::Update()
{
	GM->Update();
	CM->Update();
	UM->Update();
}

void Game_Demo::Render()
{
	GM->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
