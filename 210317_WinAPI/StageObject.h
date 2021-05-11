#pragma once
#include "GameNode.h"
#include "config.h"
class StageObject : public GameNode
{
protected:
	FPOINT pos;
	FPOINT size;
public:
	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT GetPos() { return pos; }
	void SetSize(FPOINT size) { this->pos = size; }
	FPOINT GetSize() { return size; }
	RECT GetBox();
};

