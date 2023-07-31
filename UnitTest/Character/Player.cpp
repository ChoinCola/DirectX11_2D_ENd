#include "stdafx.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
	: Character(position, size)
{
	{
		Texture2D* srcTex = new Texture2D(TexturePath + L"jelda.png");
		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

		Vector2 RunD_endPos = Vector2(texSize.x, texSize.y * .25f);
		Vector2 RunL_staPos = Vector2(0, texSize.y * .25f);
		Vector2 RunL_endPos = Vector2(texSize.x, texSize.y * .5f);
		Vector2 RunU_staPos = Vector2(0, texSize.y * .5f);
		Vector2 RunU_endPos = Vector2(texSize.x, texSize.y * .75f);
		Vector2 RunR_staPos = Vector2(0, texSize.y * .75f);
		Vector2 RunR_endPos = texSize;

		AnimationClip* RunD = new AnimationClip(L"RunD", srcTex, 10, Values::ZeroVec2, RunD_endPos);
		AnimationClip* RunL = new AnimationClip(L"RunL", srcTex, 10, RunL_staPos, RunL_endPos);
		AnimationClip* RunU = new AnimationClip(L"RunU", srcTex, 10, RunU_staPos, RunU_endPos, true);
		AnimationClip* RunR = new AnimationClip(L"RunR", srcTex, 10, RunR_staPos, RunR_endPos, true);

		animator->AddAnimClip(RunD);
		animator->AddAnimClip(RunL);
		animator->AddAnimClip(RunU);
		animator->AddAnimClip(RunR);
		animator->SetCurrentAnimClip(L"RunD");

		animRect->SetAnimator(animator);

		SAFE_DELETE(srcTex);

	}

	collision = new BoundingBox
	(animRect->GetPosition(), animRect->GetSize(), animRect->GetRotation(), Color(1, 0, 0, .35f));
}

Player::~Player()
{
	SAFE_DELETE(collision);
}

void Player::Update()
{
	animator->Update();
	animRect->Update();

	Vector3 size = animRect->GetSize() + Vector3(0, 150, 0);
	Vector3 position = animRect->GetPosition() + Vector3(100, 0, 0);
	collision->Update(position, size, 0.f);
}

void Player::Render()
{
	animRect->Render();
	collision->Render();
}
