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

	virtual void Update();
	virtual void Render();
	void Chack_Collision();
	void Chack_HP();

protected:

	SingletonBase<std::list<Character*>> Character_list;
	SingletonBase<std::list<Item*>> Item_list;

private:
	bool isPrime(Character* input);
};