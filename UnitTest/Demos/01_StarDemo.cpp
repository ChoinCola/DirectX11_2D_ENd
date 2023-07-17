#include "stdafx.h"
#include "01_StarDemo.h"

#include "Geomatries/Star.h"

void StarDemo::Init()
{
	star = new Star(Vector3(100,100,0), Vector3(100,100,0),0);
}

void StarDemo::Destroy()
{
	SAFE_DELETE(star);
}

void StarDemo::Update()
{
	star->Update();
}

void StarDemo::Render()
{
	star->Render();
}

void StarDemo::PostRender()
{
}

void StarDemo::GUI()
{
}
