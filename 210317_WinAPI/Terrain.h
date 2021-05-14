#pragma once
#include "GameNode.h"
#include "StageObject.h"
#include "TerrainInfo.h"

class Structure;
class Stage;
class Terrain : public StageObject
{
private:
	Stage* parentStage;
	Structure* structure;
	TerrainType type;
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
	void SetStage(Stage* parentStage);
	Stage* GetStage();
	void SetStructure(Structure* structure);
	Structure* GetStructure();
};

