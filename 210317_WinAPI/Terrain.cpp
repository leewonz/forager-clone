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

void Terrain::Updatef()
{
}

void Terrain::Render(HDC hdc)
{
	if (isLand)
	{
		parentStage->GetTerrainInfo(type)->GetImg()->
			FrameRender(hdc, pos.x, pos.y, 0, 0, false);
	}
	else
	{
		parentStage->GetTerrainInfo(type)->GetImg()->
			FrameRender(hdc, pos.x, pos.y, 3, 0, false);
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

void Terrain::SetStage(Stage* parentStage)
{
	this->parentStage = parentStage;
}

Stage* Terrain::GetStage()
{
	return parentStage;
}
