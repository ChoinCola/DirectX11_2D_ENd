#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"
#include "Item.h"

class Character
{
public:
	Character(Vector3 position, Vector3 size);
	virtual ~Character();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void Follow(Item& st, const D3DXVECTOR2 direc, 
	const float xsk = 100, const float ysk = 0);
	void SetSpeed(const float speed);
	auto GetmoveP();
	auto Getspeed()->float;
	
protected:

	float speed = NULL;
	int front;

	D3DXVECTOR2 moveP;
	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;
};