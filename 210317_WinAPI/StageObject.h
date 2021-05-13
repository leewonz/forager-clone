#pragma once
#include "GameNode.h"
#include "config.h"
class StageObject : public GameNode
{
protected:
	FPOINT pos;
	FPOINT offset;
	FPOINT size;
public:
	StageObject();

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return pos; }
	inline void SetOffset(FPOINT offset) { this->offset = offset; }
	inline FPOINT GetOffset() { return offset; }
	inline void SetSize(FPOINT size) { this->size = size; }
	inline FPOINT GetSize() { return size; }
	RECT GetBox();
	void CenterOffset();
};

