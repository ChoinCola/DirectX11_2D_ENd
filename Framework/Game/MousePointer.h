#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

#include "Systems/Mouse.h"

enum Mouse_state
{
	IDLE,
	ON_OBJECT,
	ON_CHARACTER,
	ON_CARD,
	ON_DATAOPEN
};

class MousePointer
{
public:
	MousePointer(Vector3 size, float Fspeed);
	~MousePointer();

	virtual void Update();
	virtual void Render();

protected:
	std::wstring MouseName;

	SingletonBase<Mouse> Mouse;
	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;

	int Mouse_state;
private:
	std::vector<Vector2> GetMouse_Image(const Vector2 Max_Size, const float x, const float y);
};

