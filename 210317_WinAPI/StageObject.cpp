#include "StageObject.h"

StageObject::StageObject()
{
    pos         = FPOINT{ 0.0f, 0.0f };
    offset      = FPOINT{ 0.0f, 0.0f };
    size        = FPOINT{ 0.0f, 0.0f };
}

RECT StageObject::GetBox()
{
    return RECT{
        (LONG)(pos.x + offset.x),
        (LONG)(pos.y + offset.y),
        (LONG)(pos.x + size.x + offset.x),
        (LONG)(pos.y + size.y + offset.y) };
}

FPOINT StageObject::GetStartPoint()
{
    return FPOINT{
        pos.x + offset.x,
        pos.y + offset.y };
}

FPOINT StageObject::GetEndPoint()
{
    return FPOINT{
        pos.x + size.x + offset.x,
        pos.y + size.y + offset.y };
}

void StageObject::CenterOffset()
{
    offset.x = -size.x * 0.5;
    offset.y = -size.y * 0.5;
}
