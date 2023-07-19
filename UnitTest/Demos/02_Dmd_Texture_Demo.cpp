#include "stdafx.h"
#include "Demos/02_Dmd_Texture_Demo.cpp.h"

#include "Geomatries/Dmd.h"

void Dmd_Texture_Demo::Init()
{
	tr = new Dmd(Vector3(WinMaxWidth /2, WinMaxHeight / 2, 0), Vector3(100, 100, 0), 0.0f, TexturePath + L"asdf.jpg");
}

void Dmd_Texture_Demo::Destroy()
{
	SAFE_DELETE(tr);

	for (Dmd* t : trs)
		SAFE_DELETE(t);
}

void Dmd_Texture_Demo::Update()
{
	tr->Update();

	/*if (Mouse::Get()->Down(0))
		trs.push_back(new Dmd(Mouse::Get()->GetPosition(), Vector3(100, 100, 1), 0.0f, TexturePath + L"asdf.jpg"));*/

	for (Dmd* t : trs)
		t->Update();
}

void Dmd_Texture_Demo::Render()
{
	tr->Render();

	for (Dmd* t : trs)
		t->Render();
}

void Dmd_Texture_Demo::PostRender()
{
}

void Dmd_Texture_Demo::GUI()
{
}
