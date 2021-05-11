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

	void InitInfo();

public:
	virtual HRESULT Init(POINT tileSize);			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	void Save();
	void Load();

	TerrainInfo* GetTerrainInfo(TerrainType i);
	void ChangeTerrain(POINT posIdx, TerrainType type, bool isLand);
};
