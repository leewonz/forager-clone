#pragma once
#include "config.h"
#include "GameNode.h"
#include "Terrain.h"
//class Terrain;

// ���
// Tile: ���������� �����ϴ� ��ĭ��ĭ 
// Terrain: ���� (��)
// Biome: ������ �׸� (�� ��)
// Floor: Terrain ���� ���� �� �ִ� ��(�ٸ� ��). Structure�� ��ġ�� �� �ְ� ��.
// Structure: �ǹ��� �ı� ������ �ڿ��� ����.

class TerrainInfo;
class Structure;
class StructureInfo;
class Stage : public GameNode
{
private:
	Terrain terrainTiles[TILE_Y][TILE_X];
	vector<Structure*> structures;

	vector<TerrainInfo*> terrainInfos;
	vector<StructureInfo*> structureInfos;

	int code[TILE_Y * TILE_X];

	void InitInfo();

public:
	virtual HRESULT Init(POINT tileSize);			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	void Save();
	void Load();

	int* EncodeTerrain();
	void DecodeTerrain(int* code);

	inline FPOINT TileToPos(POINT pos) {
		return FPOINT{ (float)(pos.x * TILESIZE), (float)(pos.y * TILESIZE) };
	}
	inline POINT PosToTile(FPOINT pos) {
		return POINT{ (LONG)(pos.x / TILESIZE), (LONG)(pos.y / TILESIZE) }; 
	};
	inline POINT PosToTile(POINT pos) {
		return POINT{ (LONG)(pos.x / TILESIZE), (LONG)(pos.y / TILESIZE) };
	};
	inline RECT PosToTile(RECT rc) {
		return RECT{ rc.left / TILESIZE, rc.top / TILESIZE ,
			         rc.right / TILESIZE, rc.bottom / TILESIZE };
	};

	bool CanBuild(RECT region);
	bool BuildStructure(POINT tilePos, int typeIdx);

	TerrainInfo* GetTerrainInfo(TerrainType i);
	StructureInfo* GetStructureInfo(int i);
	void ChangeTerrain(POINT posIdx, TerrainType type, bool isLand);
};

