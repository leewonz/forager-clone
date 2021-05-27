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
	TerrainType type;
	int floorIdx;
	POINT framePos;
	bool isLand;
	bool isFree;

public:
	virtual HRESULT Init(Stage* parentStage);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetTerrainType(TerrainType type);
	TerrainType GetTerrainType();
	void SetIsLand(bool isLand);
	bool GetIsLand();
	void SetIsFree(bool isLand);
	bool GetIsFree();
	inline void SetFloorIdx(int floorIdx) { this->floorIdx = floorIdx; }
	inline int GetFloorIdx() { return floorIdx; }
	void SetStage(Stage* parentStage);
	Stage* GetStage();
	void SetStructure(Structure* structure);
	Structure* GetStructure();
	void RefreshTileShape();
};

