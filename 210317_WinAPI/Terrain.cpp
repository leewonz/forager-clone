#include "Terrain.h"
#include "TerrainInfo.h"
#include "Stage.h"
#include "Image.h"
#include "Camera.h"

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
	FPOINT camPos = Camera::GetSingleton()->WorldToCamera(FPOINT{ (float)box.left, (float)box.top });
	//parentStage->GetTerrainInfo(type)->GetImg()->
	//	FrameRender(hdc, camPos.x, camPos.y, framePos.x, framePos.y, false);
	parentStage->GetTerrainInfo(type)->GetImg()->
		StageRender(hdc, box.left, box.top, framePos.x, framePos.y, false, 1);
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

void Terrain::RefreshTileShape()
{
	int code = 0;
	int currCode = 1;
	for (int i = 0; i < 4; i++)
	{
		POINT myPos = parentStage->PosToTile(pos);

		myPos.x += dirPoints[i].x;
		myPos.y += dirPoints[i].y;

		if (parentStage->IsInStage(myPos))
		{
			Terrain* adjTerrain = GetStage()->GetTerrain(myPos);
			if (adjTerrain->GetIsLand())
			{
				code += currCode;
			}
		}
		currCode *= 2;
	}
	framePos = parentStage->GetAdjTileShape(code, this->GetIsLand());
}
