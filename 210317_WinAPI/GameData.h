#pragma once
#include "Singleton.h"
#include "config.h"

class Image;
enum class ItemType
{
	NONE,
	PICKAXE,
	SWORD,
	SHOVEL,
	FOOD,
	MATERIAL,
	STRUCTURE,
	FLOOR,
	POTION,
	END
};


enum class TerrainType { GRASS, DESERT, WINTER, GRAVEYARD, FIRE, END };

enum class FloorType { BRIDGE, END };

struct ItemInfo
{
	int idx;
	Image* img;
	ItemType type;
	string codename;
	string name;
};

struct FloorInfo
{
	int idx;
	Image* img;
	string codename;
	string name;
};

struct Item
{
	int idx;
	int count;
};

class StructureInfo;
class TerrainInfo;
class GameData : public Singleton<GameData>
{
private:
	char iniDir[128] = "\\data\\gameData.ini";
	vector<ItemInfo> itemInfos;
	vector<TerrainInfo*> terrainInfos;
	vector<StructureInfo*> structureInfos;
	vector<FloorInfo*> floorInfos;
public:
	HRESULT Init();
	virtual HRESULT InitSingleton();
	void Release();
	void InitItemInfo();
	void InitTileInfo();
	void InitStructureInfo();
	void InitFloorInfo();
	inline ItemInfo* GetItemInfo(int idx) { return &itemInfos[idx]; }
	inline TerrainInfo* GetTerrainInfo(TerrainType i) {return terrainInfos[(int)i]; }
	inline StructureInfo* GetStructureInfo(int i) {return structureInfos[i];}
	inline FloorInfo* GetFloorInfo(int i) {return floorInfos[i];}
	void Save();
};