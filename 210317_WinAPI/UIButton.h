#pragma once
#include "UIObject.h"
class Image;
class UIButton : public UIObject
{
    Image* img;
    UI_MESSAGE defaultMessage;
};

