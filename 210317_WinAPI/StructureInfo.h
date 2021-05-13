#pragma once
#include "config.h"

class Image;
class StructureInfo
{
	int typeIdx;
	Image* img;
	string codename;
	string name;
	POINT tileSize;

public:
	void Init(int typeIndex, string imgName, string codeName);
	inline Image* GetImg() { return img; };
	inline string GetCodename() { return codename; };
	inline void SetCodename(string codename) { this->codename = codename; };
	inline POINT GetTileSize() { return tileSize; };
	inline void SetTileSize(POINT tileSize) { this->tileSize = tileSize; };
};

