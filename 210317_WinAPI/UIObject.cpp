#include "UIObject.h"

UIObject::UIObject()
{
	pos = FPOINT{ 0, 0 };
	size = FPOINT{ 0, 0 };
	isActive = true;
	parent = nullptr;
	scene = nullptr;
}

UIObject::UIObject(UIObject* parentUI)
{
	pos = FPOINT{ 0, 0 };
	size = FPOINT{ 0, 0 };
	isActive = true;
	this->parent = parent;
	scene = nullptr;
}

FPOINT UIObject::GetRelativePos()
{
	FPOINT pos = { 0, 0 };
	if (parent)
	{
		FPOINT relativePos = parent->GetRelativePos();
		pos.x += relativePos.x;
		pos.y += relativePos.y;
	}
	return pos;
}

RECT UIObject::GetBox()
{
	return RECT{
		(LONG)(pos.x),
		(LONG)(pos.y),
		(LONG)(pos.x + size.x),
		(LONG)(pos.y + size.y) };
}