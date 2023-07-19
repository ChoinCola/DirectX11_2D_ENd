#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/01_StarDemo.h"
#include "Demos/01_RectDemo.h"
#include "Demos/02_TextureDemo.h"
#include "Demos/02_Dmd_Texture_Demo.cpp.h"
#include "Demos/03_ShadedDemo.h"
#include "Demos/04_BlurDemo.h"
#include "Demos/05_RenderingTargetDemo.h"
#include "Demos/06_CollisionDemo.h"
#include "Demos/07_AnimationDemo.h"
#include "Demos/08_PlayerDemo.h"
#include "Demos/09_TileMapDemo.h"

void Program::Init()
{
	Camera::Create();
	States::Create();

	//Push(new StarDemo);
	//Push(new RectDemo);
	//Push(new Dmd_Texture_Demo);
	//Push(new ShadedDemo);
	Push(new BlurDemo);
	//Push(new RenderingTargetDemo);
	//Push(new CollisionDemo);
	//Push(new AnimationDemo);
	//Push(new PlayerDemo);
	//Push(new TileMapDemo);
}

void Program::Destroy()
{
	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
	Camera::Delete();
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();

	Camera::Get()->Update();
}

void Program::Render()
{
	for (IObject* obj : objs)
		obj->Render();

	Camera::Get()->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
