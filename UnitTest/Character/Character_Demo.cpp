#include "stdafx.h"
#include "Character_Demo.h"

Character_Demo::Character_Demo(Vector3 position, Vector3 size)
	: Character(position, size)
{
#pragma region Start_Set
	{
		delay = 0;
		angle_attack = 0;
		Character_Name = L"Goblin";
	}
#pragma endregion
	Attack_now = false;
	dch = true;
	Fspeed = 1.f / 6.f;
	animator = new Animator();
	SetSpeed(200);
#pragma region Animation
	{
		Texture2D* idle = new Texture2D(LCharacter + L"Goblin/goblin_idle_spritesheet.png");
		Texture2D* MoveR = new Texture2D(LCharacter + L"Goblin/goblin_run_spritesheet.png");

		AnimationClip* RunR = new AnimationClip(L"RunR", MoveR, 6, Values::ZeroVec2, { MoveR->GetWidth(), MoveR->GetHeight() }, 0, Fspeed);
		AnimationClip* RunL = new AnimationClip(L"RunL", MoveR, 6, { MoveR->GetWidth(), 0 }, { 0, MoveR->GetHeight() }, true, Fspeed);
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
	(animRect->GetPosition(), animRect->GetSize(), animRect->GetRotation(), Color(1, 0, 0, 0.35f));

	HPB = new HPBar(
		animRect->GetPosition(), { 100 , (animRect->GetSize().y / 6), 0 },
		&HP, &HPdefault);
	HPBar_list.Get()->push_back(HPB);

	hand = new Goblin_Sword(position, Vector3(50, 50, 1), this);
	Item_list.Get()->push_back(hand);
}

Character_Demo::~Character_Demo()
{
	Character_list.Get()->remove(this);
}

void Character_Demo::Move()
{
	auto key = Keyboard::Get();
	auto delta = Time::Delta();

	// 방향판별
	if (key->Press('W')) { moveP.y = +1; }
	if (key->Press('A')) { moveP.x = -1; front = 0; }
	if (key->Press('S')) { moveP.y = -1; }
	if (key->Press('D')) { moveP.x = +1; front = 1; }

	// 이동판별
	if (abs(moveP.x) || abs(moveP.y)) {
		if (front) { animator->SetCurrentAnimClip(L"RunR"); }
		else { animator->SetCurrentAnimClip(L"RunL"); }
		SetNormalize(moveP, speed, delta);
	}
	else {
		if (front) { animator->SetCurrentAnimClip(L"IdleR"); }
		else { animator->SetCurrentAnimClip(L"IdleL"); }
	}

	// 이동 초기화
	moveP = { 0, 0 };
}
void Character_Demo::Attack(const float Attack_speed = 1, const float Attack_delay = 0)
{
	auto delta = Time::Delta();
	auto key = Keyboard::Get();

	if (Attack_now == true || (key->Press('F') && delay >= Attack_delay)) {
		Attack_now = true;
		hand->Setphysical(1);

		if ((angle_attack >= 90 || angle_attack <= -90)) {

			angle_attack = 0;
			hand->GetanimRect()->SetRotation(angle_attack);
			Attack_now = false;
			delay = 0;
			dch = true;
			D3DXMatrixTranslation(&hand->GetanimRect()->GetCenterPoint(),
				0,
				0,
				0);

			return;
		}

		else if (front) angle_attack -= delta * 100 * Attack_speed;
		else angle_attack += delta * 100 * Attack_speed;

		{
			D3DXMatrixTranslation(&hand->GetanimRect()->GetCenterPoint(),
				hand->Getaniator()->GetTexelFrameSize().x * 30,
				hand->Getaniator()->GetTexelFrameSize().y * 30,
				animRect->GetPosition().z);

		}
	}
	else { hand->Setphysical(0); }

	if (delay <= Attack_delay) { delay += delta; }

	hand->GetanimRect()->SetRotation(angle_attack);
}

void Character_Demo::Update()
{
	__super::Update();
	Attack(5, 1);
	Move();
	Follow(*hand, 60, 1);

	animator->Update();
	animRect->Update();
	{
		collision->Update(animRect->GetPosition(), animRect->GetSize(), 0.f);
	}
}

void Character_Demo::Render()
{
	animRect->Render();
	collision->Render();
	__super::Render();
}
