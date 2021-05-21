#include "GameData.h"

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