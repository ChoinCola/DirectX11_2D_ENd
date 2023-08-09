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
	SAFE_DELETE(hand);

	for (auto def : HPBar_Black)
		SAFE_DELETE(def)
}

void Character::Update()
{
	Damage_Chack();
	{
		HPBar->UpdateProgressBar(HP / HPdefault);
		HPBar->Update(animRect->GetPosition());

		for (auto def : HPBar_Black)
		{
			def->Update(animRect->GetPosition());
		}
	}
}

void Character::Render()
{
	HPBar->Render();
	for (auto def : HPBar_Black)
		def->Render();
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
		{ 100 , (animRect->GetSize().y / 6), 0 },
		0.0f, D3DXCOLOR(255, 0, 0, 1), UI::LEFT_TO_RIGHT);
	{
		HPBar_Black.push_back(new ProgressBar({ HPBar->GetPosition().x + 
												HPBar->GetSize().x / 2, 
												HPBar->GetPosition().y, 0 },
			{ HPBar->GetSize().x, HPBar->GetSize().y + HPBar->GetSize().y / 2, 0},
			0.0f, HPPath + L"HP_BAR_MIDDLE.png"));

		HPBar_Black.push_back(new ProgressBar({ HPBar_Black[0]->GetPosition().x -
												HPBar_Black[0]->GetSize().x / 2,
												HPBar_Black[0]->GetPosition().y, 0 }
		,{ 4, HPBar_Black[0]->GetSize().y, 1 },0.0f, HPPath + L"HP_BAR_LEFT_PEAK.png"));

		HPBar_Black.push_back(new ProgressBar({ HPBar_Black[0]->GetPosition().x +
												HPBar_Black[0]->GetSize().x / 2,
												HPBar_Black[0]->GetPosition().y, 0 }
		,{ 4, HPBar_Black[0]->GetSize().y, 1 },0.0f, HPPath + L"HP_BAR_LEFT_PEAK.png"));
	}
}
