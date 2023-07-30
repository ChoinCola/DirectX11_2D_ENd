#include "stdafx.h"
#include "Character_Demo.h"


Character_Demo::Character_Demo(Vector3 position, Vector3 size)
	: Character(position, size)
{
	animRect->SetSpeed(200);
	Fspeed = 1.f/6.f;
	animator = new Animator();

	#pragma region Animation
	{
		Texture2D* idle = new Texture2D(LCharacter + L"Goblin/goblin_idle_spritesheet.png");
		Texture2D* MoveR = new Texture2D(LCharacter + L"Goblin/goblin_run_spritesheet.png");

		AnimationClip* RunR = new AnimationClip(L"RunR", MoveR, 6, Values::ZeroVec2, { MoveR->GetWidth(), MoveR->GetHeight()}, 0, Fspeed);
		AnimationClip* RunL = new AnimationClip(L"RunL", MoveR, 6, { MoveR->GetWidth(), 0 }, {0, MoveR->GetHeight()}, true, Fspeed);
		AnimationClip* IdleR = new AnimationClip(L"IdleR", idle, 6, Values::ZeroVec2, { MoveR->GetWidth(), MoveR->GetHeight() }, 0, Fspeed);
		AnimationClip* IdleL = new AnimationClip(L"IdleL", idle, 6, { MoveR->GetWidth() ,0 }, { 0, MoveR->GetHeight() }, 0, Fspeed);

		animator->AddAnimClip(RunR);
		animator->AddAnimClip(RunL);
		animator->AddAnimClip(IdleR);
		animator->AddAnimClip(IdleL);

		animator->SetCurrentAnimClip(L"IdleR");
		animRect->SetAnimator(animator);

		SAFE_DELETE(idle);
		SAFE_DELETE(MoveR);
	}
	#pragma endregion

	collision = new BoundingBox
	(animRect->GetPosition(), animRect->GetSize(), animRect->GetRotation(), Color(1, 0, 0, .35f));

	Sword = new Goblin_Sword(position, Vector3(1000, 100, 1), animRect);
}

Character_Demo::~Character_Demo()
{
}

void Character_Demo::Update()
{
	animRect->Move();
	animator->Update();
	animRect->Update();

	Sword->Update();


	Vector3 size = animRect->GetSize() + Vector3(0, 150, 0);
	Vector3 position = animRect->GetPosition() + Vector3(100, 0, 0);
	collision->Update(position, size, 0.f);
}

void Character_Demo::Render()
{

	animRect->Render();
	collision->Render();
	Sword->Render();
}
