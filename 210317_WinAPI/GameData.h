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
	COIN,
	END
};

enum class TerrainType { GRASS, DESERT, WINTER, GRAVEYARD, FIRE, END };

enum class StructureCategory { BUILDING, RESOURCE, END };

enum class FloorCategory { NONE, NORMAL, BRIDGE, END };

enum class ConstructionCategory { STRUCTURE, FLOOR, END };

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

struct ConstructionRecipe
{
	int idx;
	Image* iconImg;
	ConstructionCategory constructionCategory;
	int constructionIdx;
	Item materials[Con::CONSTRUCTION_MATERIAL_MAX];
};

struct CraftingRecipe
{
	int idx;
	int resultItemIdx;
	int structureIdx;
	Item materials[Con::CRAFTING_MATERIAL_MAX];
	float craftingTime;
};

class StructureInfo;
class TerrainInfo;
class GameData : public Singleton<GameData>
{
public:
	static const Item EMPTY_ITEM;

private:
	char iniDir[128] = "\\data\\gameData.ini";
	vector<ItemInfo> itemInfos;
	vector<TerrainInfo*> terrainInfos;
	vector<StructureInfo*> structureInfos;
	vector<FloorInfo> floorInfos;
	vector<ConstructionRecipe> constructionRecipes;
	vector<CraftingRecipe> craftingRecipes;

	string itemCategoryNames[(int)ItemCategory::END]
	{
		"NONE",
		"PICKAXE",
		"SWORD",
		"SHOVEL",
		"FOOD",
		"MATERIAL",
		"FLOOR",
		"POTION",
		"COIN"
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
	void InitConstructionRecipe();
	void InitCraftingRecipe();

	inline ItemInfo* GetItemInfo(int idx) { return &itemInfos[idx]; }
	inline TerrainInfo* GetTerrainInfo(TerrainType i) {return terrainInfos[(int)i]; }
	inline StructureInfo* GetStructureInfo(int i) {return structureInfos[i];}
	inline FloorInfo* GetFloorInfo(int i) {return &floorInfos[i];}
	inline ConstructionRecipe* GetConstructionRecipe(int i) {return &constructionRecipes[i];}
	inline CraftingRecipe* GetCraftingRecipe(int i) {return &craftingRecipes[i];}

	inline int GetItemInfoCount() { return itemInfos.size(); }
	inline int GetTerrainInfoCount() { return terrainInfos.size(); }
	inline int GetStructureInfoCount() { return structureInfos.size(); }
	inline int GetFloorInfoCount() { return floorInfos.size(); }
	inline int GetConstructionRecipeCount() { return constructionRecipes.size(); }
	inline int GetCraftingRecipeCount() { return craftingRecipes.size(); }

	inline string GetTerrainTypeName(int i) { return terrainTypeNames[i]; }

	int FindItemInfo(string codeName);
	int FindStructureInfo(string codeName);
	int FindFloorInfo(string codeName);

	vector<CraftingRecipe*> GetStructureCraftingRecipes(int structureIdx);

	void Save();
};