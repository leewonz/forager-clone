#include "StageObject.h"

RECT StageObject::GetBox()
{
    return RECT{
        (LONG)(pos.x - (size.x * 0.5f)),
        (LONG)(pos.y - (size.y * 0.5f)),
        (LONG)(pos.x + (size.x * 0.5f)),
        (LONG)(pos.y + (size.y * 0.5f)) };
}
