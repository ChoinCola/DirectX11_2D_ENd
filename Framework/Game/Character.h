#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

#include "Game/UI/ProgressBar.h"

#include "Item.h"

class Character
{

public:
	Character(Vector3 position, Vector3 size, std::wstring Character_Name = L"UnFound");
	virtual ~Character();

	virtual void Update();
	virtual void Render();

	virtual void Damage_Chack();

	void Follow(Item& st, const float xsk = 100, const float ysk = 0);
	void SetSpeed(const float speed);
	auto GetmoveP();
	auto Getspeed()->float;
	auto GetHP() { return HP; }
	Item* GetItem() { return hand; }
	const std::wstring GetName() { return Character_Name; }
	BoundingBox& Getcollision() { return *collision; }

	std::list<Item*>& Get_hit_calculation() { return hit_calculation; }
	void Push_Damage(Item* damage) { hit_calculation.push_back(damage); }

protected:
	float damage; // 공격력
	bool dch; // 공격여부 ( OBB 겹쳤을 때 한번만 적용되도록
	float HP; // 채력
	float HPdefault;
	float speed = NULL;
	int front;

	std::list<Item*> hit_calculation;

	D3DXVECTOR2 moveP;

	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;
	BoundingBox* collision = nullptr;
	ProgressBar* HPBar = nullptr;
	Item* hand = nullptr;

	std::wstring Character_Name;
private:
	void HPbar();

};