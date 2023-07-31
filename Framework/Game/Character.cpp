#include "Framework.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size)
{
	front = 0;
	moveP = {0, 0};
	speed = 100;
	animRect = new AnimationRect(position, size);
	animator = new Animator();
}

Character::~Character()
{
	SAFE_DELETE(animRect);
	SAFE_DELETE(animator);
}

void Character::SetSpeed(const float speed)
{
	this->speed = speed;
}

auto Character::GetmoveP()
{
	return moveP;
}

auto Character::Getspeed() -> float
{
	return speed;
}

void Character::Follow(Item &st, const D3DXVECTOR2 direc, const float xsk, const float ysk)
{
	if (front) { 
	st.Getaniator()->SetCurrentAnimClip(L"IdleR"); 
	st.GetanimRect()->SetPosition
	(animRect->GetPosition().x + (direc.x + xsk),
		animRect->GetPosition().y + ysk);
	}
	else { 
	st.Getaniator()->SetCurrentAnimClip(L"IdleL"); 
	st.GetanimRect()->SetPosition
	(animRect->GetPosition().x - (direc.x + xsk),
		animRect->GetPosition().y + ysk);
	}
}
