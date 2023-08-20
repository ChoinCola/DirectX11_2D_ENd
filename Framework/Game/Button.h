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
	bool GetPress() { return Press; };

	bool GetUP() { return UP; };
	std::wstring GetName() { return Button_name; };
	Vector3 GetSize() { return Size; };
	Vector3 GetPosition() { return Mark_Default_Position; };
	bool GetRender() { return Render_now; };
	void SetRender() { Render_now ? Render_now = false : Render_now = true; };
	void SetPosition(const Vector3 position) { Mark_Default_Position = position; };

protected:
	bool Render_now;
	bool Push_now; // 눌려있으면 true
	bool Press; // 눌렸을때 단 한번만 반환하고 다시 true로 전환.
	bool Press_b; // 눌렸을때 단 한번만 반환하고 다시 true로 전환.
	bool UP; // 올라와있으면 true

	std::wstring Button_name;

	TextureRect* Button_Default = nullptr;
	TextureRect* Button_Push = nullptr;
	TextureRect* Button_Mark = nullptr;

	Vector3 Mark_Default_Position;
	Vector3 Size;
};

