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
	HPbar();
}

Character::~Character()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(animRect);
	SAFE_DELETE(animator);
	SAFE_DELETE(HPBar);
	SAFE_DELETE(HPBar_Black)
	SAFE_DELETE(hand);
}

void Character::Update()
{
	Damage_Chack();
	{
		HPBar->UpdateProgressBar(HP / HPdefault);
		HPBar->Update(animRect->GetPosition());

		HPBar_Black->Update(animRect->GetPosition());
	}
}

void Character::Render()
{
	HPBar_Black->Render();
	HPBar->Render();
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

void Character::HPbar()
{

	HPBar = new ProgressBar({ -50, (animRect->GetSize().y / 2) + 20, 0 },
		{ animRect->GetSize().x , (animRect->GetSize().y / 5), 0 },
		0.0f, D3DXCOLOR(255, 0, 0, 1), UI::LEFT_TO_RIGHT);

	HPBar_Black = new ProgressBar({ -50, (animRect->GetSize().y / 2) + 20, 0 },
		{ animRect->GetSize().x , (animRect->GetSize().y / 5), 0 },
		0.0f, D3DXCOLOR(0, 0, 0, 1), UI::LEFT_TO_RIGHT);

	HPBar_Black->UpdateProgressBar(1);
}
