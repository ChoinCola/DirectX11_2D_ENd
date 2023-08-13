#include "stdafx.h"
#include "10_Game_Demo.h"



void Game_Demo::Init()
{	
	GM = new Game_Master();
	mp = new MousePointer(Vector3{50, 50, 0});
	cd = new Card_Demo();
	ui = new UI_Master();
	ef = new Character_Master();
	ShowCursor(false);

	GM->Chack_ALL_LIST();
}

void Game_Demo::Destroy()
{
}

void Game_Demo::Update()
{
	
	ef->Update();
	mp->Update();
	cd->Update();
	ui->Update();
}

void Game_Demo::Render()
{
	ef->Render();
	cd->Render();
	ui->Update();

	mp->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
