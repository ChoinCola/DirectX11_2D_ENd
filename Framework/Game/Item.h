#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

class Item
{
public:
	Item(Vector3 position, Vector3 size);
	virtual ~Item();

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;
};