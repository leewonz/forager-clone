#pragma once
#include "GameNode.h"
#include "StageObject.h"
#include "TerrainInfo.h"
#include "GameData.h"
#include <bitset>

const POINT dirPoints[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

class Structure;
class Stage;
class Terrain : public StageObject
{
private:
	Stage* parentStage;
	Structure* structure;
	TerrainType category;
	int floorIdx;
	POINT framePos;
	bool isLand;
	bool isFree;

public:
	virtual HRESULT Init(Stage* parentStage);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetTerrainType(TerrainType category);
	TerrainType GetTerrainType();
	void SetIsLand(bool isLand);
	bool GetIsLand();
	void SetIsFree(bool isLand);
	bool GetIsFree();
	void SetFloorIdx(int floorIdx);
	int GetFloorIdx();
	void SetStage(Stage* parentStage);
	Stage* GetStage();
	void SetStructure(Structure* structure);
	Structure* GetStructure();
	void RefreshTileShape();
};

