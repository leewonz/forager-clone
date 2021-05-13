#pragma once
#include "config.h"
#include "GameNode.h"
#include "Terrain.h"
//class Terrain;

// 용어
// Tile: 스테이지를 구성하는 한칸한칸 
// Terrain: 지형 (땅)
// Biome: 지형의 테마 (땅 색)
// Floor: Terrain 위에 놓을 수 있는 것(다리 등). Structure를 설치할 수 있게 함.
// Structure: 건물과 파괴 가능한 자원을 포함.

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
	virtual HRESULT Init(POINT tileSize);			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

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

