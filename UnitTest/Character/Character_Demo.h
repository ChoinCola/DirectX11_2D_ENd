#pragma once
#include "Game/Character.h"
#include "Item_Object/Sword.h"

class Character_Demo : public Character
{
public:
	Character_Demo(Vector3 position, Vector3 size);
	~Character_Demo();

	virtual void Update() override;
	virtual void Render() override;

private:
	Goblin_Sword* Sword = nullptr;
	BoundingBox* collision = nullptr;
	float Fspeed;
};
