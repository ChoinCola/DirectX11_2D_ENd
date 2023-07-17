#include "stdafx.h"
#include "04_BlurDemo.h"

#include "Geomatries/BlurTexture.h"

void BlurDemo::Init()
{
	bt = new BlurTexture(Vector3(640, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.f, TexturePath + L"asdf.jpg");
}

void BlurDemo::Destroy()
{
	SAFE_DELETE(bt);
}

void BlurDemo::Update()
{
	bt->Update();
}

void BlurDemo::Render()
{
	bt->Render();
}

void BlurDemo::PostRender()
{

}

void BlurDemo::GUI()
{
	bt->GUI();
}