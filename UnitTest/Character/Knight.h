#pragma once
#include "Game/Character.h"
#include "Item_Object/Knight_Sword.h"
#include "math.h"

class Knight : public Character
{
public:
	Knight(Vector3 position, Vector3 size);
	~Knight();

	virtual void Update() override;
	virtual void Render() override;
	void Move();
	void Attack(const float Attack_speed, const float Attack_delay);

private:
	void SetNormalize(D3DXVECTOR2& move, const int speed, const float delta);
	Knight_Sword* Sword = nullptr;
	BoundingBox* collision = nullptr;

	bool Attack_now = false;
	float Fspeed;

	float delay;
	double angle_attack;

};