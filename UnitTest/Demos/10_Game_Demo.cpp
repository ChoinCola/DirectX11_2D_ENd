#include "stdafx.h"
#include "10_Game_Demo.h"

#include "Geomatries/Game_Demo/Character_Demo.h"

void Game_Demo::Init()
{
	tr = new Character_Demo(Vector3(640, 360, 0), Vector3(500, 500, 1), 0.0f, TexturePath + L"asdf.png");
}

void Game_Demo::Destroy()
{
	SAFE_DELETE(tr);

	for (Character_Demo* t : trs)
		SAFE_DELETE(t);
}

void Game_Demo::Update()
{
	tr->Update();

	if (Mouse::Get()->Down(0))
		trs.push_back(new Character_Demo(Mouse::Get()->GetPosition(), Vector3(500, 500, 1), 0.0f, TexturePath + L"asdf.jpg"));

	for (Character_Demo* t : trs)
		t->Update();
}

void Game_Demo::Render()
{
	tr->Render();

	for (Character_Demo* t : trs)
		t->Render();
}

void Game_Demo::PostRender()
{
}

void Game_Demo::GUI()
{
}
