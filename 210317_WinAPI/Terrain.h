#pragma once
#include "GameNode.h"
#include "StageObject.h"
#include "TerrainInfo.h"

class Stage;
class Terrain : public StageObject
{
private:
	Stage* parentStage;
	TerrainType type;
	POINT framePos;
	bool isLand;

public:
	virtual HRESULT Init(Stage* parentStage);
	virtual void Release();
	virtual void Update();
	void Updatef();
	virtual void Render(HDC hdc);

	void SetTerrainType(TerrainType type);
	TerrainType GetTerrainType();
	void SetIsLand(bool isLand);
	bool GetIsLand();
	void SetStage(Stage* parentStage);
	Stage* GetStage();
};

