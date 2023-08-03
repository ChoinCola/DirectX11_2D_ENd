#include "stdafx.h"
#include "10_Game_Demo.h"

#include "Character/Character_Demo.h"
#include "Character/Knight.h"

void Game_Demo::Init()
{
	tr = new Character_Demo(Vector3(640, 360, 0), Vector3(100, 100, 1));
	kn = new Knight(Vector3(640, 360, 0), Vector3(100, 100, 1));
}

void Game_Demo::Destroy()
{
	SAFE_DELETE(tr);
	SAFE_DELETE(kn);

}

void Game_Demo::Update()
{
	tr->Update();
	kn->Update();

}

void Game_Demo::Render()
{
	tr->Render();
	kn->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
