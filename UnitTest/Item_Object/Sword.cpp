#include "stdafx.h"
#include "Sword.h"


Goblin_Sword::Goblin_Sword(Vector3 position, Vector3 size, AnimationRect* Host)
	: Item(position, size), Host(Host)
{
	Fspeed = 1;
	animator = new Animator();

#pragma region Animation
	{
		Texture2D* idle = new Texture2D(LItem + L"goblin_knife.png");

		AnimationClip* IdleR = new AnimationClip(L"IdleR", idle, 1, Values::ZeroVec2, { idle->GetWidth(), idle->GetHeight() }, 0, Fspeed);
		AnimationClip* IdleL = new AnimationClip(L"IdleL", idle, 1, { idle->GetWidth() ,0 }, { 0, idle->GetHeight() }, 0, Fspeed);

		animator->AddAnimClip(IdleR);
		animator->AddAnimClip(IdleL);

		animator->SetCurrentAnimClip(L"IdleR");
		animRect->SetAnimator(animator);

		SAFE_DELETE(idle);
	}
#pragma endregion
	collision = new BoundingBox
	(animRect->GetPosition(), animRect->GetSize(), animRect->GetRotation(), Color(1, 0, 0, .35f));
}

Goblin_Sword::~Goblin_Sword()
{
}

void Goblin_Sword::Update()
{

	animRect->Follow(Host->GetPosition(), Host->GetmoveP() * 100);
	animator->Update();
	animRect->Update();

	Vector3 size = animRect->GetSize() + Vector3(0, 150, 0);
	Vector3 position = animRect->GetPosition() + Vector3(100, 0, 0);
	collision->Update(position, size, 0.f);
}

void Goblin_Sword::Render()
{
	animRect->Render();
	collision->Render();
}