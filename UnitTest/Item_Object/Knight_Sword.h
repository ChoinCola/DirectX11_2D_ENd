#pragma once
 #include "Game/Item.h"
 #include "Game/Character.h"

class Knight_Sword : public Item
{
public:
	Knight_Sword(Vector3 position, Vector3 size, Character* Host);
	~Knight_Sword();

	virtual void Update() override;
	virtual void Render() override;

private:

	Character* Host = nullptr;
	float Fspeed;
};
