#include "GameData.h"
#include "TerrainInfo.h"
#include "StructureInfo.h"

HRESULT GameData::Init()
{
	InitItemInfo();
	InitTileInfo();
	InitStructureInfo();
	InitFloorInfo();
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
	info.name = "bone";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 2;
	info.category = ItemCategory::MATERIAL;
	info.codename = "flower";
	info.name = "flower";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 3;
	info.category = ItemCategory::MATERIAL;
	info.codename = "stone";
	info.name = "stone";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 4;
	info.category = ItemCategory::MATERIAL;
	info.codename = "wood";
	info.name = "wood";
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
	tempStructureInfo->Init(0, "structure_furnace", "furnace");
	tempStructureInfo->SetTileSize(POINT{ 2, 2 });
	tempStructureInfo->SetImgOffset(POINT{ 1, -10 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(1, "structure_forge", "forge");
	tempStructureInfo->SetTileSize(POINT{ 2, 2 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -4 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(2, "structure_sewingStation", "sewingStation");
	tempStructureInfo->SetTileSize(POINT{ 2, 2 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -16 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(3, "structure_tree_grass", "tree_grass");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -32 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(3, "structure_tree_fire", "tree_fire");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -32 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(3, "structure_tree_snow", "tree_snow");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ 0, -32 });
	structureInfos.push_back(tempStructureInfo);

	tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(3, "structure_tree_desert", "tree_desert");
	tempStructureInfo->SetTileSize(POINT{ 1, 1 });
	tempStructureInfo->SetImgOffset(POINT{ -16, -32 });
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
	tempFloorInfo.name = "bridge";
	tempFloorInfo.category = FloorCategory::BRIDGE;
	tempFloorInfo.img = ImageManager::GetSingleton()->FindImage("floor_" + tempFloorInfo.codename);
	floorInfos.push_back(tempFloorInfo);
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
