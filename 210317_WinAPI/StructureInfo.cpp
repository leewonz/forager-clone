#include "StructureInfo.h"

void StructureInfo::Init(int typeIndex, string codename, string name)
{
	img = ImageManager::GetSingleton()->FindImage(codename);
	this->typeIdx = typeIndex;
	this->codename = codename;
	this->name = name;
	this->tileSize = POINT{ 1, 1 };
}
