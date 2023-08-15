#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"
#include "Demos/10_Game_Demo.h"

void Program::Init()
{
	Camera::Create();
	States::Create();

	//Push(new StarDemo);
	//Push(new RectDemo);
	//Push(new Dmd_Texture_Demo);
	//Push(new ShadedDemo);
	//Push(new BlurDemo);
	//Push(new RenderingTargetDemo);
	//Push(new CollisionDemo);
	//Push(new AnimationDemo);
	//Push(new PlayerDemo);
	//Push(new TileMapDemo);
	Push(new Game_Demo);
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
