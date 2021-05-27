#pragma once
#include "config.h"
#include "GameNode.h"
#include "Terrain.h"
#include <bitset>
//class Terrain;

// 용어
// Tile: 스테이지를 구성하는 한칸한칸 
// Terrain: 지형 (땅)
// Biome: 지형의 테마 (땅 색)
// Floor: Terrain 위에 놓을 수 있는 것(다리 등). Structure를 설치할 수 있게 함.
// Structure: 건물과 파괴 가능한 자원을 포함.


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
	virtual HRESULT Init(POINT tileSize);			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)
	virtual void RenderLine(HDC hdc, int tileY);	// 프레임 단위로 출력 (이미지, 텍스트 등)

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

