#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"
#include "Item.h"

class Character
{
public:
	Character(Vector3 position, Vector3 size);
	virtual ~Character();

	virtual void Update();
	virtual void Render() = 0;

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

	float damage; // ���ݷ�
	bool dch; // ���ݿ��� ( OBB ������ �� �ѹ��� ����ǵ���
	int HP; // ä��
	float speed = NULL;
	int front;

	std::list<Item*>* hit_calculation = nullptr;

	D3DXVECTOR2 moveP;

	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;

	BoundingBox* collision = nullptr;

	Item* hand = nullptr;
};