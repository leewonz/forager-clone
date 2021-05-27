#pragma once
#include "config.h"
#include "GameData.h"

class Image;
class StructureInfo
{
	int typeIdx;
	float hp;
	StructureCategory category;
	Image* img;
	POINT imgOffset;
	string codename;
	string name;
	POINT tileSize;

public:
	void Init(int typeIndex, string codename, string name);
	inline Image* GetImg() { return img; };
	inline string GetCodename() { return codename; };
	inline void SetCodename(string codename) { this->codename = codename; };
	inline POINT GetTileSize() { return tileSize; };
	inline void SetTileSize(POINT tileSize) { this->tileSize = tileSize; };
	inline POINT GetImgOffset() { return imgOffset;};
	inline void SetImgOffset(POINT imgOffset) { this->imgOffset = imgOffset; };
	inline StructureCategory GetCategory() { return category; };
	inline void SetCategory(StructureCategory category) { this->category = category; };
};

