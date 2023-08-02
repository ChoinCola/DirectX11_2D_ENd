#include "Framework.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size)
	:	front(0) , moveP({0, 0}), speed(100), damage(10), HP(100)
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

void Character::Follow(Item &st, const float xsk, const float ysk)
{
	auto delta = Time::Delta();
	static double my = 0;

	if (my >= 360) my = 0;
	else my += (1 * delta) * 10;

	if (front) { 
	st.Getaniator()->SetCurrentAnimClip(L"IdleR"); 
	st.GetanimRect()->SetPosition
	(animRect->GetPosition().x + xsk,
		animRect->GetPosition().y + (sin(my) * ysk));
	}
	else { 
	st.Getaniator()->SetCurrentAnimClip(L"IdleL"); 
	st.GetanimRect()->SetPosition
	(animRect->GetPosition().x - xsk,
		animRect->GetPosition().y + (sin(my) * ysk));
	}
}
