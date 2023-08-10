#include "Framework.h"
#include "MousePointer.h"

MousePointer::MousePointer(Vector3 size)
{
	animRect = new AnimationRect(Mouse.Get()->GetPosition(),size);
	animator = new Animator();

	Mouse_state = IDLE;
#pragma region Animation
	{
		Texture2D* idle = new Texture2D(LUI + L"Crosshair/stylesheet_green.png");

		// x14 y11
		Vector2 texSize		= { idle->GetWidth(),idle->GetHeight() };

		AnimationClip* Idle = new AnimationClip(L"Idle", idle, 1, GetMouse_Image(texSize, 3, 2), 0, 1);
		AnimationClip* On_object = new AnimationClip(L"On_object", idle, 1, GetMouse_Image(texSize, 8, 2), 0, 1);

		animator->AddAnimClip(Idle);
		animator->AddAnimClip(On_object);

		animator->SetCurrentAnimClip(L"Idle");

		animRect->SetAnimator(animator);

		SAFE_DELETE(idle);
	}
#pragma endregion
}

MousePointer::~MousePointer()
{
	SAFE_DELETE(animRect);
	SAFE_DELETE(animator);
}

void MousePointer::Update()
{	
	switch (Mouse_state)
	{
	case(IDLE) :
	{
		animator->SetCurrentAnimClip(L"Idle");
		animRect->SetPosition(Mouse.Get()->GetPosition().x + animRect->GetSize().x / 7,
							  Mouse.Get()->GetPosition().y - animRect->GetSize().y / 4);
		break;
	}
	case(ON_OBJECT) :
	{
		animator->SetCurrentAnimClip(L"On_object");
		animRect->SetPosition(Mouse.Get()->GetPosition().x + animRect->GetSize().x / 4, 
							  Mouse.Get()->GetPosition().y - animRect->GetSize().y / 4);
		break;
	}
	case(ON_CHARACTER):
	{
		break;
	}
	case(ON_CARD):
	{
		break;
	}
	case(ON_DATAOPEN):
	{
		break;
	}
	default:
		break;
	}

	animator->Update();
	animRect->Update();
}

void MousePointer::Render()
{
	animRect->Render();
}

std::vector<Vector2> MousePointer::GetMouse_Image(const Vector2 Max_Size, const float x, const float y)
{
	return std::vector<Vector2> { 
	{ Max_Size.x / 14 * (x - 1.f), Max_Size.y / 11 * (y - 1.f) }, 
	{ Max_Size.x / 14 * x, Max_Size.y / 11 * y } };
}
