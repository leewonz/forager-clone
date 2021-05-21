#pragma once
#include "UIObject.h"
#include "config.h"
class UIContainer : public UIObject
{
	multimap<int, UIObject> children;
};

