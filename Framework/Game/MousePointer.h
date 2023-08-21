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
	MousePointer(Vector3 size = { 50,50,0 });
	~MousePointer();
	void Update();
	void Render();
	int GetMosueState() { return Mouse_state; };
	void SetMouseState(int def) { Mouse_state = def; };
	D3DXVECTOR3* GetMousePointer() { return &Worldposition; };
	SingletonBase<Mouse>* GetMouse() { return &Mouse; };

protected:
	std::wstring MouseName;
	D3DXVECTOR3 Worldposition;
	SingletonBase<Mouse> Mouse;
	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;

	int Mouse_state;
private:
	std::vector<Vector2> GetMouse_Image(const Vector2 Max_Size, const float x, const float y);
};

