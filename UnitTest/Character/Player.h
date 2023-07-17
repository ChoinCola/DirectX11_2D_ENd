#pragma once

#include "Game/Character.h"

class Player : public Character
{
public:
	Player(Vector3 position, Vector3 size);
	~Player();

	virtual void Update() override;
	virtual void Render() override;

private:
	BoundingBox* collision = nullptr;
};