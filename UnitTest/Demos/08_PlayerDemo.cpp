#include "stdafx.h"
#include "08_PlayerDemo.h"

#include "Character/Player.h"
#include "UI/HUD.h"

void PlayerDemo::Init()
{
	player = new Player({ 100,100,0 }, { 100,100,1 });
	float width = WinMaxWidth / 2;
	float height = WinMaxHeight / 2;
	map = new TextureRect(Vector3(width, height, 0), Vector3(1024, 672, 0), 0.f, TexturePath + L"Map.png");

	hud = new HUD();

	Sounds::Get()->AddSound("BGM", SoundPath + L"lego.mp3");
	Sounds::Get()->AddSound("ez", SoundPath + L"ez.wav");
	Sounds::Get()->Play("BGM", 0.5f);
}

void PlayerDemo::Destroy()
{
	SAFE_DELETE(hud);
	SAFE_DELETE(map);
	SAFE_DELETE(player);
}

void PlayerDemo::Update()
{
	map->Update();
	player->Update();

	hud->Update();

	if (Keyboard::Get()->Down(VK_F2))
		Sounds::Get()->Play("ez", 0.3f);
}

void PlayerDemo::Render()
{
	map->Render();
	player->Render();

	hud->Render();
}

void PlayerDemo::PostRender()
{
	Text::Get()->BeginDraw();
	{
		wstring str = L"TEXT ÅØ½ºÆ® ¡Ù¡×";
		float size = (float)Text::Get()->GetStringWidth(str, 5.0f);
		Vector2 pos = Vector2(0, 0);
		Text::Get()->RenderText(str, pos, Color(1, 0, 1, 1), size, false);
	}
	Text::Get()->EndDraw();
}

void PlayerDemo::GUI()
{
}
