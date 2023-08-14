#pragma once

class Knight : public Character, public IGame_Master
{
public:
	Knight(Vector3 position, Vector3 size);
	~Knight();

	virtual void Update() override;
	virtual void Render() override;
	void Move();
	void Attack(const float Attack_speed, const float Attack_delay);


private:
	bool Attack_now = false;
	float Fspeed;

	float delay;
	float angle_attack;
};