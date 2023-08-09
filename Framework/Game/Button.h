#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"


class Button
{
public:
	Button(Vector3 position, Vector3 size, std::wstring Button_Name,
	std::wstring Button_Default, std::wstring Button_Push, std::wstring Button_Mark);
	virtual ~Button();

	virtual void Update();
	virtual void Update(Vector3 position);

	virtual void Render();
	
protected:
	bool Push_now;

	std::wstring Button_name;

	TextureRect* Button_Default = nullptr;
	TextureRect* Button_Push = nullptr;
	TextureRect* Button_Mark = nullptr;

	Vector3 Mark_Default_Position;
};

