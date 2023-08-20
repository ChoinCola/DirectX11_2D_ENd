#include "Framework.h"
#include "Character.h"


Character::Character(Vector3 position, Vector3 size, std::wstring Character_Name)
	: front(0), moveP({ 0, 0 }), speed(100), HP(100)
{
	front = 0;
	moveP = { 0, 0 };
	speed = 100;
	animRect = new AnimationRect(position, size);
	animator = new Animator();
	HPdefault = HP;

}

Character::~Character()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(animRect);
	SAFE_DELETE(animator);
	SAFE_DELETE(hand);
}

void Character::Update()
{
	Damage_Chack();
}

void Character::Render()
{
}

void Character::SetSpeed(const float speed)
{
	this->speed = speed;
}

void Character::SetNormalize(D3DXVECTOR2& move, const float speed, const float delta)
{
	D3DXVec2Normalize(&move, &move);
	animRect->SetPosition
	(animRect->GetPosition().x + (move.x * speed * delta),
		animRect->GetPosition().y + (move.y * speed * delta));
}

auto Character::GetmoveP()
{
	return moveP;
}

auto Character::Getspeed() -> float
{
	return speed;
}

void Character::Damage_Chack()
{
	if (!hit_calculation.empty())
	{
		for (auto def = hit_calculation.begin();
			def != hit_calculation.end();)
		{
			if ((*def)->Getphysical() == 0)
			{
				HP -= (*def)->GetDamage();
				cout << String::ToString(GetName()) <<
					" IS HIT" << endl;

				cout << String::ToString(L"Damage!") <<
					(*def)->GetDamage() << endl;

				cout << HP << endl;

				def = hit_calculation.erase(def);
			}
			else { ++def; }
		}
	}
}

void Character::Follow(Item& st, const float xsk, const float ysk)
{
	
	auto delta = Time::Delta();

	static double my = 0;
	float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	if (my >= 360) my = 0;
	else my += (randomValue * delta) * 10;

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