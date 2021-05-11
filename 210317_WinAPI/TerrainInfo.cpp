#include "GameNode.h"
#include "TerrainInfo.h"
#include "Stage.h"
#include "Image.h"
#include "ImageManager.h"

void TerrainInfo::Init(int typeIndex, string imgName)
{
	img = ImageManager::GetSingleton()->FindImage(imgName);
	this->typeIndex = typeIndex;
}

Image* TerrainInfo::GetImg()
{
	return img;
}
