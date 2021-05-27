#pragma once
#include "Singleton.h"
#include "config.h"

class Image;
enum class ItemCategory
{
	NONE,
	PICKAXE,
	SWORD,
	SHOVEL,
	FOOD,
	MATERIAL,
	FLOOR,
	POTION,
	END
};

enum class TerrainType { GRASS, DESERT, WINTER, GRAVEYARD, FIRE, END };

enum class StructureCategory { BUILDING, RESOURCE, END };

enum class FloorCategory { NONE, NORMAL, BRIDGE, END };

struct ItemInfo
{
	int idx;
	Image* img;
	ItemCategory category;
	string codename;
	string name;
};

struct FloorInfo
{
	int idx;
	Image* img;
	FloorCategory category;
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
	vector<FloorInfo> floorInfos;

	string itemCategoryNames[(int)ItemCategory::END]
	{
		"NONE",
		"PICKAXE",
		"SWORD",
		"SHOVEL",
		"FOOD",
		"MATERIAL",
		"FLOOR",
		"POTION"
	};

	string terrainTypeNames[(int)TerrainType::END]
	{
		"GRASS", "DESERT", "WINTER", "GRAVEYARD", "FIRE"
	};

	string structureCategoryNames[(int)StructureCategory::END]
	{
		"BUILDING", "RESOURCE"
	};

	string floorCategoryNames[(int)FloorCategory::END]
	{
		"NONE", "NORMAL", "BRIDGE",
	};

public:
	HRESULT Init();
	virtual HRESULT InitSingleton();
	void Release();
	void InitNames();
	void InitItemInfo();
	void InitTileInfo();
	void InitStructureInfo();
	void InitFloorInfo();
	inline ItemInfo* GetItemInfo(int idx) { return &itemInfos[idx]; }
	inline TerrainInfo* GetTerrainInfo(TerrainType i) {return terrainInfos[(int)i]; }
	inline StructureInfo* GetStructureInfo(int i) {return structureInfos[i];}
	inline FloorInfo* GetFloorInfo(int i) {return &floorInfos[i];}
	int FindItemInfo(string codeName);
	int FindStructureInfo(string codeName);
	int FindFloorInfo(string codeName);
	void Save();
};