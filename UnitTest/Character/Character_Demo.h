#pragma once

class Character_Demo : public Character, public IGame_Master
{
public:
	Character_Demo(Vector3 position, Vector3 size);
	~Character_Demo();

	virtual void Update() override;
	virtual void Render() override;
	void Move();
	void Attack(const float Attack_speed, const float Attack_delay);


private:
	bool Attack_now = false;
	float Fspeed;

	float delay;
	float angle_attack;
}; /*{ -50, (animRect->GetSize().y / 2) + 20, 0 }*/