#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"
#include "Systems/Mouse.h"
#include "Game/MousePointer.h"

class Button
{
public:
	Button(Vector3 position, Vector3 size, std::wstring Button_Name,
	std::wstring Button_Default, std::wstring Button_Push, std::wstring Button_Mark);
	virtual ~Button();

	virtual void Update();
	virtual void Render();

	void Push() { Push_now ? Push_now = false : Push_now = true; };
	bool GetPush() { return Push_now; };
	bool GetUP() { return UP; };
	std::wstring GetName() { return Button_name; };
	Vector3 GetSize() { return Size; };
	Vector3 GetPosition() { return Mark_Default_Position; };
	bool GetRender() { return Render_now; };
	void SetRender() { Render_now ? Render_now = false : Render_now = true; };

protected:
	bool Render_now;
	bool Push_now;
	bool UP;

	std::wstring Button_name;

	TextureRect* Button_Default = nullptr;
	TextureRect* Button_Push = nullptr;
	TextureRect* Button_Mark = nullptr;

	Vector3 Mark_Default_Position;
	Vector3 Size;
};

