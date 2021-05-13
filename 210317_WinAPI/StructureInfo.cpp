#include "StructureInfo.h"

void StructureInfo::Init(int typeIndex, string imgName, string codeName)
{
	img = ImageManager::GetSingleton()->FindImage(imgName);
	this->typeIdx = typeIndex;
	this->codename = codename;
	this->tileSize = POINT{ 1, 1 };
}
