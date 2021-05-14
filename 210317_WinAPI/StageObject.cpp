#include "StageObject.h"

StageObject::StageObject()
{
    pos         = FPOINT{ 0.0f, 0.0f };
    offset      = FPOINT{ 0.0f, 0.0f };
    size        = FPOINT{ 0.0f, 0.0f };
}

//void StageObject::SetPos(FPOINT pos)
//{ 
//    this->pos = pos;
//}
//
//FPOINT StageObject::GetPos()
//{
//    return pos;
//}
//
//void StageObject::SetOffset(FPOINT offset)
//{
//    this->offset = offset;
//}
//
//FPOINT StageObject::GetOffset()
//{
//    return offset;
//}
//
//void StageObject::SetSize(FPOINT size)
//{
//    this->size = size;
//}
//
//FPOINT StageObject::GetSize()
//{
//    return size;
//}

RECT StageObject::GetBox()
{
    return RECT{
        (LONG)(pos.x + offset.x),
        (LONG)(pos.y + offset.y),
        (LONG)(pos.x + size.x + offset.x),
        (LONG)(pos.y + size.y + offset.y) };
}

void StageObject::CenterOffset()
{
    offset.x = -size.x * 0.5;
    offset.y = -size.y * 0.5;
}
