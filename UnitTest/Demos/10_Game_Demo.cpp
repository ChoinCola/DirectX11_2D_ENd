#include "stdafx.h"
#include "10_Game_Demo.h"



void Game_Demo::Init()
{
	mp = new MousePointer(Vector3{50, 50, 0});
	cd = new Card_Demo();
	ui = new UI_Master();
	ef = new Character_Master();
	ShowCursor(false);
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
