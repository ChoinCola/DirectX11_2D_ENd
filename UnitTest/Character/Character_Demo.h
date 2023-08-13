#pragma once

#include "Game/Character.h"
#include "Item_Object/Goblin_Sword.h"
#include "math.h"
class Character_Demo : public Character
{
public:
	Character_Demo(Vector3 position, Vector3 size);
	~Character_Demo();

	virtual void Update() override;
	virtual void Render() override;
	void Move();
	void Attack(const float Attack_speed, const float Attack_delay);


private:
	void SetNormalize(D3DXVECTOR2& move, const int speed, const float delta);

	bool Attack_now = false;
	float Fspeed;

	float delay;
	float angle_attack;
};