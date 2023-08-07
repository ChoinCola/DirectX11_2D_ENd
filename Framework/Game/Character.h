#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

#include "Game/UI/ProgressBar.h"

#include "Item.h"

class Character
{

public:
	Character(Vector3 position, Vector3 size);
	virtual ~Character();

	virtual void Update();
	virtual void Render();

	virtual void Damage_Chack();

	void Follow(Item& st, const float xsk = 100, const float ysk = 0);
	void SetSpeed(const float speed);
	auto GetmoveP();
	auto Getspeed()->float;
	Item* GetItem() { return hand; }
	BoundingBox& Getcollision() { return *collision; }

	std::list<Item*>* Get_hit_calculation() { return hit_calculation;}
	void Push_Damage(Item* damage) { hit_calculation->push_back(damage); }

protected:
	float damage; // 공격력
	bool dch; // 공격여부 ( OBB 겹쳤을 때 한번만 적용되도록
	float HP; // 채력
	float HPdefault;
	float speed = NULL;
	int front;

	std::list<Item*>* hit_calculation = nullptr;

	D3DXVECTOR2 moveP;

	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;

	BoundingBox* collision = nullptr;

	ProgressBar* HPBar = nullptr;

	Item* hand = nullptr;

private:
	void HPbar();

};