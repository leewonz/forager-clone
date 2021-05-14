#include "Terrain.h"
#include "TerrainInfo.h"
#include "Stage.h"
#include "Image.h"

HRESULT Terrain::Init(Stage* parentStage)
{
	SetStage(parentStage);
	return S_OK;
}

void Terrain::Release()
{
}

void Terrain::Update()
{
}

void Terrain::Render(HDC hdc)
{
	RECT box = GetBox();
	if (isLand)
	{
		parentStage->GetTerrainInfo(type)->GetImg()->
			FrameRender(hdc, box.left, box.top, 0, 0, false);
	}
	else
	{
		parentStage->GetTerrainInfo(type)->GetImg()->
			FrameRender(hdc, box.left, box.top, 3, 0, false);
	}
}

void Terrain::SetTerrainType(TerrainType type)
{
	this->type = type;
}

TerrainType Terrain::GetTerrainType()
{
	return type;
}

void Terrain::SetIsLand(bool isLand)
{
	this->isLand = isLand;
}

bool Terrain::GetIsLand()
{
	return isLand;
}

void Terrain::SetIsFree(bool isFree)
{
	this->isFree = isFree;
}

bool Terrain::GetIsFree()
{
	return isFree;
}

void Terrain::SetStage(Stage* parentStage)
{
	this->parentStage = parentStage;
}

Stage* Terrain::GetStage()
{
	return parentStage;
}

void Terrain::SetStructure(Structure* structure)
{
	this->structure = structure;
}

Structure* Terrain::GetStructure()
{
	return structure;
}
