#pragma once

#include "Utilities/SingletonBase.h"
#include "Game/Character.h"
#include "Game/Item.h"
#include "math.h"

class Character_Master 
{
public:
	Character_Master();
	~Character_Master();

	void Update();
	void Render();
	void Chack_Collision();

	BoundingBox& Getcollision() { return *collision; }

protected:

	SingletonBase<std::vector<Character*>>* Character_list;
	SingletonBase<std::vector<Item*>>* Item_list;

	BoundingBox* collision = nullptr;
};