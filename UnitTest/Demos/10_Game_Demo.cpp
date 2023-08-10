#include "stdafx.h"
#include "10_Game_Demo.h"



void Game_Demo::Init()
{
	cd = new Card_Demo();
	ef = new Battle_Master();
	mp = new MousePointer(Vector3{50, 50, 0});
	ui = new UI_Master();
	ShowCursor(false);
}

void Game_Demo::Destroy()
{
}

void Game_Demo::Update()
{
	ef->Update();
	mp->Update();
	ui->Update();
}

void Game_Demo::Render()
{
	ef->Render();

	ui->Render();



	mp->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
