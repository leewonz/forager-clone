#pragma once
#include "config.h"
#include "GameNode.h"
#include "Terrain.h"
#include <bitset>
//class Terrain;

// ���
// Tile: ���������� �����ϴ� ��ĭ��ĭ 
// Terrain: ���� (��)
// Biome: ������ �׸� (�� ��)
// Floor: Terrain ���� ���� �� �ִ� ��(�ٸ� ��). Structure�� ��ġ�� �� �ְ� ��.
// Structure: �ǹ��� �ı� ������ �ڿ��� ����.


class Structure;

class Stage : public GameNode
{
private:
	Terrain terrainTiles[Con::TILE_Y][Con::TILE_X];
	vector<Structure*> structures;

	enum AdjDirs {R = 1, D = 2, L = 4, U = 8};
	POINT adjTileShape[16];
	POINT adjTileShapeWater[2];

	int code[Con::TILE_Y * Con::TILE_X];

	void InitInfo();

public:
	virtual HRESULT Init(POINT tileSize);			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)
	virtual void RenderLine(HDC hdc, int tileY);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	void Save();
	void Load();

	int* EncodeTerrain();
	void DecodeTerrain(int* code);

	inline FPOINT TileToPos(POINT pos) 
	{
		return FPOINT{ (float)(pos.x * Con::TILESIZE), (float)(pos.y * Con::TILESIZE) };
	}

	inline POINT PosToTile(FPOINT pos) 
	{
		return POINT{ (LONG)(pos.x / Con::TILESIZE), (LONG)(pos.y / Con::TILESIZE) };
	};

	inline POINT PosToTile(POINT pos) 
	{
		return POINT{ (LONG)(pos.x / Con::TILESIZE), (LONG)(pos.y / Con::TILESIZE) };
	};

	inline RECT PosToTile(RECT rc) 
	{
		return RECT{ rc.left / Con::TILESIZE, rc.top / Con::TILESIZE ,
					 rc.right / Con::TILESIZE, rc.bottom / Con::TILESIZE };
	};

	inline bool IsInStage(POINT tilePos)
	{
		return (tilePos.y >= 0 && tilePos.y < Con::TILE_Y &&
			    tilePos.x >= 0 && tilePos.x < Con::TILE_X);
	};
	inline POINT GetAdjTileShape(int code, bool isLand) 
	{
		if (isLand)
		{
			return adjTileShape[code];
		}
		else
		{
			return adjTileShapeWater[(code & AdjDirs::U) ? 1 : 0];
		}
		
	}

	bool CanBuild(RECT region);
	bool BuildStructure(POINT tilePos, int typeIdx);
	void RefreshTileShapeAll();

	Terrain* GetTerrain(POINT TilePos);

	void ChangeTerrain(POINT posIdx, TerrainType category, bool isLand);
};

