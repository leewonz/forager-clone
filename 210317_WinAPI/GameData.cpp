#include "GameData.h"
#include "TerrainInfo.h"
#include "StructureInfo.h"

const Item GameData::EMPTY_ITEM = Item{ 0, 0 };

HRESULT GameData::Init()
{
	InitItemInfo();
	InitTileInfo();
	InitStructureInfo();
	InitFloorInfo();
	InitConstructionRecipe();
	InitCraftingRecipe();
	return S_OK;
}

HRESULT GameData::InitSingleton()
{
	Init();
	return S_OK;
}

void GameData::Release()
{
	for (int i = 0; i < structureInfos.size(); i++)
	{
		SAFE_DELETE(structureInfos[i]);
	}
	for (int i = 0; i < terrainInfos.size(); i++)
	{
		SAFE_DELETE(terrainInfos[i]);
	}
}

void GameData::InitNames()
{
}

void GameData::InitItemInfo()
{
	//struct ItemInfo
	//{
	//	int idx;
	//	ItemCategory category;
	//	string codename;
	//	string name;
	//};

	ItemInfo info;

	info.idx = 0;
	info.category = ItemCategory::NONE;
	info.codename = "noneItem";
	info.name = "";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 1;
	info.category = ItemCategory::MATERIAL;
	info.codename = "bone";
	info.name = "Bone";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 2;
	info.category = ItemCategory::MATERIAL;
	info.codename = "flower";
	info.name = "Flower";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 3;
	info.category = ItemCategory::MATERIAL;
	info.codename = "stone";
	info.name = "Stone";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 4;
	info.category = ItemCategory::MATERIAL;
	info.codename = "wood";
	info.name = "Wood";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 5;
	info.category = ItemCategory::MATERIAL;
	info.codename = "coal";
	info.name = "Coal";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 6;
	info.category = ItemCategory::MATERIAL;
	info.codename = "ironOre";
	info.name = "Iron Ore";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);
	
	info.idx = 7;
	info.category = ItemCategory::MATERIAL;
	info.codename = "goldOre";
	info.name = "Gold Ore";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);
	
	info.idx = 8;
	info.category = ItemCategory::MATERIAL;
	info.codename = "ironIngot";
	info.name = "Iron Ingot";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);
	
	info.idx = 9;
	info.category = ItemCategory::MATERIAL;
	info.codename = "goldIngot";
	info.name = "Gold Ingot";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);
	
	info.idx = 10;
	info.category = ItemCategory::COIN;
	info.codename = "coin";
	info.name = "Coin";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);
		
	info.idx = 11;
	info.category = ItemCategory::MATERIAL;
	info.codename = "brick";
	info.name = "Brick";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

}

void GameData::InitTileInfo()
{
	for (int i = 0; i < (int)TerrainType::END; i++)
	{
		TerrainInfo* tempTerrainInfo = new TerrainInfo();
		switch ((TerrainType)i)
		{
		case TerrainType::GRASS:
			tempTerrainInfo->Init(i, "tile_grass");
			break;
		case TerrainType::DESERT:
			tempTerrainInfo->Init(i, "tile_desert");
			break;
		case TerrainType::WINTER:
			tempTerrainInfo->Init(i, "tile_winter");
			break;
		case TerrainType::GRAVEYARD:
			tempTerrainInfo->Init(i, "tile_graveyard");
			break;
		case TerrainType::FIRE:
			tempTerrainInfo->Init(i, "tile_fire");
			break;
		}
		terrainInfos.push_back(tempTerrainInfo);
	}
}

void GameData::InitStructureInfo()
{
	StructureInfo* tempStructureInfo;

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(0, "furnace", "Furnace");
	tempStructureInfo->SetTileSize(POINT{ 2, 2 });
	tempStructureInfo->SetImgOffset(POINT{ 1, -12 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("stone"), 10 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(1, "forge", "Forge");
	tempStructureInfo->SetTileSize(POINT{ 2, 2 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -4 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("brick"), 4 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("ironIngot"), 4 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(2, "sewingStation", "Sewing Station");
	tempStructureInfo->SetTileSize(POINT{ 2, 2 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -18 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("wood"), 10 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("brick"), 4 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(3, "tree_grass", "tree_grass");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -32 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("wood"), 2 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(4, "tree_fire", "tree_fire");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -32 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("wood"), 2 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(5, "tree_snow", "tree_snow");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -32 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("wood"), 2 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(6, "tree_desert", "tree_desert");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ -16, -32 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("wood"), 2 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(7, "stone", "stone");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -1 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("stone"), 3 });
	structureInfos.push_back(tempStructureInfo);
	
	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(8, "coal", "coal");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -1 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("stone"), 1 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("coal"), 2 });
	structureInfos.push_back(tempStructureInfo);
	
	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(9, "iron", "iron");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -1 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("stone"), 1 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("ironOre"), 2 });
	structureInfos.push_back(tempStructureInfo);
	
	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(10, "gold", "gold");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -1 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("stone"), 1 });
	tempStructureInfo->AddDrop(Item{ FindItemInfo("goldOre"), 2 });
	structureInfos.push_back(tempStructureInfo);

}

void GameData::InitFloorInfo()
{
	FloorInfo tempFloorInfo;

	tempFloorInfo.idx = 0;
	tempFloorInfo.codename = "noneFloor";
	tempFloorInfo.name = "";
	tempFloorInfo.category = FloorCategory::NONE;
	tempFloorInfo.img = nullptr;
	floorInfos.push_back(tempFloorInfo);

	tempFloorInfo.idx = 1;
	tempFloorInfo.codename = "bridge";
	tempFloorInfo.name = "Bridge";
	tempFloorInfo.category = FloorCategory::BRIDGE;
	tempFloorInfo.img = ImageManager::GetSingleton()->FindImage("floor_" + tempFloorInfo.codename);
	floorInfos.push_back(tempFloorInfo);
}

void GameData::InitConstructionRecipe()
{
	ConstructionRecipe tempConstructionRecipe;
	string tempCodename;

	tempConstructionRecipe = ConstructionRecipe();
	tempCodename = "furnace";
	tempConstructionRecipe.idx = 0;
	tempConstructionRecipe.constructionCategory = ConstructionCategory::STRUCTURE;
	tempConstructionRecipe.constructionIdx = FindStructureInfo(tempCodename);
	tempConstructionRecipe.iconImg = ImageManager::GetSingleton()->FindImage("ui_icon_" + tempCodename);
	tempConstructionRecipe.materials[0] = Item{ FindItemInfo("stone"), 10 };
	tempConstructionRecipe.materials[1] = Item{ FindItemInfo("item_none"), 0};
	tempConstructionRecipe.materials[2] = Item{ FindItemInfo("item_none"), 0 };
	tempConstructionRecipe.materials[3] = Item{ FindItemInfo("item_none"), 0 };
	constructionRecipes.push_back(tempConstructionRecipe);

	tempConstructionRecipe = ConstructionRecipe();
	tempCodename = "forge";
	tempConstructionRecipe.idx = 1;
	tempConstructionRecipe.constructionCategory = ConstructionCategory::STRUCTURE;
	tempConstructionRecipe.constructionIdx = FindStructureInfo(tempCodename);
	tempConstructionRecipe.iconImg = ImageManager::GetSingleton()->FindImage("ui_icon_" + tempCodename);
	tempConstructionRecipe.materials[0] = Item{ FindItemInfo("brick"), 4 };
	tempConstructionRecipe.materials[1] = Item{ FindItemInfo("ironIngot"), 4 };
	tempConstructionRecipe.materials[2] = Item{ FindItemInfo("item_none"), 0 };
	tempConstructionRecipe.materials[3] = Item{ FindItemInfo("item_none"), 0 };
	constructionRecipes.push_back(tempConstructionRecipe);

	tempConstructionRecipe = ConstructionRecipe();
	tempCodename = "bridge";
	tempConstructionRecipe.idx = 2;
	tempConstructionRecipe.constructionCategory = ConstructionCategory::FLOOR;
	tempConstructionRecipe.constructionIdx = FindFloorInfo(tempCodename);
	tempConstructionRecipe.iconImg = ImageManager::GetSingleton()->FindImage("ui_icon_" + tempCodename);
	tempConstructionRecipe.materials[0] = Item{ FindItemInfo("wood"), 4 };
	tempConstructionRecipe.materials[1] = Item{ FindItemInfo("item_none"), 0 };
	tempConstructionRecipe.materials[2] = Item{ FindItemInfo("item_none"), 0 };
	tempConstructionRecipe.materials[3] = Item{ FindItemInfo("item_none"), 0 };
	constructionRecipes.push_back(tempConstructionRecipe);
}

void GameData::InitCraftingRecipe()
{
	// coal brick ironIngot goldIngot coin

	//int idx;
	//int resultItemIdx;
	//int structureIdx;
	//Item materials[Con::CRAFTING_MATERIAL_MAX];
	//float craftingTime;

	CraftingRecipe tempCraftingRecipe;

	tempCraftingRecipe = CraftingRecipe();
	tempCraftingRecipe.idx = 0;
	tempCraftingRecipe.resultItemIdx = FindItemInfo("coal");
	tempCraftingRecipe.structureIdx = FindStructureInfo("furnace");
	tempCraftingRecipe.materials[0] = Item{FindItemInfo("wood"), 2};
	tempCraftingRecipe.materials[1] = EMPTY_ITEM;
	tempCraftingRecipe.materials[2] = EMPTY_ITEM;
	tempCraftingRecipe.materials[3] = EMPTY_ITEM;
	tempCraftingRecipe.craftingTime = 1.0f;
	craftingRecipes.push_back(tempCraftingRecipe);

	tempCraftingRecipe = CraftingRecipe();
	tempCraftingRecipe.idx = 1;
	tempCraftingRecipe.resultItemIdx = FindItemInfo("brick");
	tempCraftingRecipe.structureIdx = FindStructureInfo("furnace");
	tempCraftingRecipe.materials[0] = Item{ FindItemInfo("stone"), 2 };
	tempCraftingRecipe.materials[1] = Item{ FindItemInfo("coal"), 1 };
	tempCraftingRecipe.materials[2] = EMPTY_ITEM;
	tempCraftingRecipe.materials[3] = EMPTY_ITEM;
	tempCraftingRecipe.craftingTime = 2.0f;
	craftingRecipes.push_back(tempCraftingRecipe);

	tempCraftingRecipe = CraftingRecipe();
	tempCraftingRecipe.idx = 2;
	tempCraftingRecipe.resultItemIdx = FindItemInfo("ironIngot");
	tempCraftingRecipe.structureIdx = FindStructureInfo("furnace");
	tempCraftingRecipe.materials[0] = Item{ FindItemInfo("ironOre"), 2 };
	tempCraftingRecipe.materials[1] = Item{ FindItemInfo("coal"), 1 };
	tempCraftingRecipe.materials[2] = EMPTY_ITEM;
	tempCraftingRecipe.materials[3] = EMPTY_ITEM;
	tempCraftingRecipe.craftingTime = 2.0f;
	craftingRecipes.push_back(tempCraftingRecipe);

	tempCraftingRecipe = CraftingRecipe();
	tempCraftingRecipe.idx = 3;
	tempCraftingRecipe.resultItemIdx = FindItemInfo("goldIngot");
	tempCraftingRecipe.structureIdx = FindStructureInfo("furnace");
	tempCraftingRecipe.materials[0] = Item{ FindItemInfo("goldOre"), 2 };
	tempCraftingRecipe.materials[1] = Item{ FindItemInfo("coal"), 1 };
	tempCraftingRecipe.materials[2] = EMPTY_ITEM;
	tempCraftingRecipe.materials[3] = EMPTY_ITEM;
	tempCraftingRecipe.craftingTime = 2.0f;
	craftingRecipes.push_back(tempCraftingRecipe);

	tempCraftingRecipe = CraftingRecipe();
	tempCraftingRecipe.idx = 4;
	tempCraftingRecipe.resultItemIdx = FindItemInfo("coin");
	tempCraftingRecipe.structureIdx = FindStructureInfo("forge");
	tempCraftingRecipe.materials[0] = Item{ FindItemInfo("goldIngot"), 1 };
	tempCraftingRecipe.materials[1] = EMPTY_ITEM;
	tempCraftingRecipe.materials[2] = EMPTY_ITEM;
	tempCraftingRecipe.materials[3] = EMPTY_ITEM;
	tempCraftingRecipe.craftingTime = 4.0f;
	craftingRecipes.push_back(tempCraftingRecipe);
}

int GameData::FindItemInfo(string codeName)
{
	for (int i = 0; i < itemInfos.size(); i++)
	{
		if (itemInfos[i].codename == codeName) { return i; }
	}
	return -1;
}

int GameData::FindStructureInfo(string codeName)
{
	for (int i = 0; i < structureInfos.size(); i++)
	{
		if (structureInfos[i]->GetCodename() == codeName) { return i; }
	}
	return -1;
}

int GameData::FindFloorInfo(string codeName)
{
	for (int i = 0; i < floorInfos.size(); i++)
	{
		if (floorInfos[i].codename == codeName) { return i; }
	}
	return -1;
}

vector<CraftingRecipe*> GameData::GetStructureCraftingRecipes(int structureIdx)
{
	vector<CraftingRecipe*> result;
	for (int i = 0; i < craftingRecipes.size(); i++)
	{
		if (craftingRecipes[i].structureIdx == structureIdx)
		{
			result.push_back(&craftingRecipes[i]);
		}
	}
	return result;
}

void GameData::Save()
{
	char Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, Path);
	//GetModuleFileName(NULL, Path, MAX_PATH);
	string strPath(Path);
	string strIniDir(iniDir);
	string strFullPath = strPath + strIniDir;
	const char* fullPath = strFullPath.c_str();

	for (int i = 0; i < itemInfos.size(); i++)
	{
		int res;
		res = WritePrivateProfileString(
			(string("Item_") + to_string(i)).c_str(),
			"idx",
			to_string(itemInfos[i].idx).c_str(),
			fullPath);
		res = WritePrivateProfileString(
			(string("Item_") + to_string(i)).c_str(),
			"category",
			itemCategoryNames[(int)itemInfos[i].category].c_str(),
			fullPath);
		res = WritePrivateProfileString(
			(string("Item_") + to_string(i)).c_str(),
			"codename",
			itemInfos[i].codename.c_str(),
			fullPath);
		res = WritePrivateProfileString(
			(string("Item_") + to_string(i)).c_str(),
			"name",
			itemInfos[i].name.c_str(),
			fullPath);
	}
}
