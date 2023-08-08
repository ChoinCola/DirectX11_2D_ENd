#include "Framework.h"
#include "Item.h"

Item::Item(Vector3 position, Vector3 size, float Mass, std::wstring Item_Name)
	: physical_q(0)
{
	animRect = new AnimationRect(position, size);
	animator = new Animator();
}

Item::~Item()
{
	SAFE_DELETE(animRect);
	SAFE_DELETE(animator);
}
