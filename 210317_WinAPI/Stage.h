#pragma once
#include "config.h"
#include "GameNode.h"
#include "Terrain.h"
//class Terrain;

class TerrainInfo;
class Stage : public GameNode
{
private:
	Terrain TerrainTiles[TILE_Y][TILE_X];
	vector<TerrainInfo*> TerrainInfos;
	int code[TILE_Y * TILE_X];

	void InitInfo();

public:
	virtual HRESULT Init(POINT tileSize);			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	void Save();
	void Load();

	int* EncodeTerrain();
	void DecodeTerrain(int* code);

	TerrainInfo* GetTerrainInfo(TerrainType i);
	void ChangeTerrain(POINT posIdx, TerrainType type, bool isLand);
};

