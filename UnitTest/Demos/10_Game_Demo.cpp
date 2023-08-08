#include "stdafx.h"
#include "10_Game_Demo.h"



void Game_Demo::Init()
{
	cd = new Card_Demo();
	ef = new Battle_Master();

}

void Game_Demo::Destroy()
{


}

void Game_Demo::Update()
{
	//cd->Update();
	ef->Update();
}

void Game_Demo::Render()
{
	//cd->Render();
	ef->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
