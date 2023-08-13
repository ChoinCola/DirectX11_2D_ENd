#pragma once
#include "Game/Item.h"
#include "Game/Character.h"

class Goblin_Sword : public Item
{
public:
	Goblin_Sword(Vector3 position, Vector3 size, Character* Host);
	~Goblin_Sword();

	virtual void Update() override;
	virtual void Render() override;

	const Character* GetHost() { return Host; }

private:

	Character* Host = nullptr;

	float Fspeed;
};
