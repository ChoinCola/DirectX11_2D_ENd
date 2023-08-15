#include "stdafx.h"
#include "Knight_Sword.h"


Knight_Sword::Knight_Sword(Vector3 position, Vector3 size, Character* Host)
	: Item(position, size), Host(Host)
{
	Mass = 15;
	Fspeed = 1;
	animator = new Animator();
	Item_Name = L"Knight_Sword";
#pragma region Animation
	{
		Texture2D* idle = new Texture2D(LItem + L"weapon_sword.png");

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

Knight_Sword::~Knight_Sword()
{
	Item_list.Get()->remove(this);
}

void Knight_Sword::Update()
{
	animRect->Update();
	collision->Update(animRect->GetPosition(), animRect->GetSize(),
		animRect->GetRotation(), animRect->GetCenterPoint());
}


void Knight_Sword::Render()
{
	animRect->Render();
	collision->Render();
}
