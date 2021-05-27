#include "GameData.h"
#include "TerrainInfo.h"
#include "StructureInfo.h"

HRESULT GameData::Init()
{
	InitItemInfo();
	InitTileInfo();
	InitStructureInfo();
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

void GameData::InitItemInfo()
{
	//struct ItemInfo
	//{
	//	int idx;
	//	ItemType type;
	//	string codename;
	//	string name;
	//};

	ItemInfo info;

	info.idx = 0;
	info.type = ItemType::NONE;
	info.codename = "noneItem";
	info.name = "";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 1;
	info.type = ItemType::MATERIAL;
	info.codename = "bone";
	info.name = "bone";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 2;
	info.type = ItemType::MATERIAL;
	info.codename = "flower";
	info.name = "flower";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 3;
	info.type = ItemType::MATERIAL;
	info.codename = "stone";
	info.name = "stone";
	info.img = ImageManager::GetSingleton()->FindImage("item_" + info.codename);
	itemInfos.push_back(info);

	info.idx = 4;
	info.type = ItemType::MATERIAL;
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
	StructureInfo* tempStructureInfo = new StructureInfo();
	tempStructureInfo->Init(0, "sampleBuilding", "sampleBuilding");
	tempStructureInfo->SetTileSize(POINT{ 2, 2 });
	structureInfos.push_back(tempStructureInfo);
}

void GameData::InitFloorInfo()
{
	FloorInfo* tempFloorInfo = new FloorInfo();
	tempFloorInfo->codename = "bridge";
	tempFloorInfo->name = "bridge";
	tempFloorInfo->idx = 0;
	tempFloorInfo->img = ImageManager::GetSingleton()->FindImage("floor_" + tempFloorInfo->codename);
	floorInfos.push_back(tempFloorInfo);
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
			"type",
			to_string((int)itemInfos[i].type).c_str(),
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
