#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

class Item
{
public:
	Item(Vector3 position, Vector3 size, float Mass = 0, std::wstring Item_Name = L"UnFound");
	virtual ~Item();

	virtual void Update() = 0;
	virtual void Render() = 0;

	auto GetanimRect() { return animRect; }
	auto Getaniator() { return animator; }
	BoundingBox& Getcollision() { return *collision; }

	auto Setphysical(float phy = 0) { physical_q = phy; }
	auto SetMass(float Mass = 0) { this->Mass = Mass; }
	auto GetDamage() { return Mass; }
	auto Getphysical() { return physical_q; }
	const std::wstring GetName() { return Item_Name; }

protected:

	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;

	BoundingBox* collision = nullptr;
	std::wstring Item_Name;

	float physical_q;
	float Mass;
};