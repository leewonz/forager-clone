#include "Terrain.h"
#include "TerrainInfo.h"

#include "Stage.h"
#include "Image.h"
#include "Camera.h"

HRESULT Terrain::Init(Stage* parentStage)
{
	SetStage(parentStage);
	isPassable = true;
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
	FPOINT startPoint = GetStartPoint();
	GameData* gameData = GameData::GetSingleton();
	//FPOINT camPos = Camera::GetSingleton()->WorldToCamera(FPOINT{ startPoint.x, startPoint.y });
	//parentStage->GetTerrainInfo(category)->GetImg()->
	//	FrameRender(hdc, camPos.x, camPos.y, framePos.x, framePos.y, false);
	gameData->GetTerrainInfo(category)->GetImg()->
		StageRender(hdc, startPoint.x, startPoint.y, framePos.x, framePos.y, false, 1);

	FloorInfo* floorInfo = gameData->GetFloorInfo(floorIdx);
	if (floorInfo->category != FloorCategory::NONE)
	{
		floorInfo->img->StageRender(
			hdc, startPoint.x, startPoint.y, 0, 0, false, 1);
	}
}

void Terrain::SetTerrainType(TerrainType category)
{
	this->category = category;
}

TerrainType Terrain::GetTerrainType()
{
	return category;
}

void Terrain::SetIsLand(bool isLand)
{
	this->isLand = isLand;
	SetIsPassable(isLand);
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

void Terrain::SetIsPassable(bool isPassable)
{
	this->isPassable = isPassable;
}

bool Terrain::GetIsPassable()
{
	return isPassable;
}

void Terrain::SetFloorIdx(int floorIdx)
{
	this->floorIdx = floorIdx;
	FloorInfo* myInfo = GameData::GetSingleton()->GetFloorInfo(floorIdx);
	switch (myInfo->category)
	{
	case FloorCategory::NONE:
		isFree = isLand;
		isPassable = isLand;
		break;
	case FloorCategory::BRIDGE:
		isFree = true;
		isPassable = true;
		break;
	}
}

int Terrain::GetFloorIdx()
{
	return floorIdx;
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
