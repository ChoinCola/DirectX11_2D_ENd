#pragma once
#include "Game/Character.h"
#include "Item_Object/Sword.h"
#include "math.h"

class Character_Demo : public Character
{
public:
	Character_Demo(Vector3 position, Vector3 size);
	~Character_Demo();

	virtual void Update() override;
	virtual void Render() override;
	void Move();
	void Attack(const float Attack_speed);

private:
	void SetNormalize(D3DXVECTOR2 &move, const int speed, const float delta);
	Goblin_Sword* Sword = nullptr;
	BoundingBox* collision = nullptr;

	bool Attack_now = false;
	float Fspeed;

	float delay;
	double angle_attack;

};
