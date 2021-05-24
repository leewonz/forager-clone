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

struct ItemInfo
{
	int idx;
	Image* img;
	ItemType type;
	string codename;
	string name;
};

struct Item
{
	int idx;
	int count;
};

class GameData : public Singleton<GameData>
{
private:
	vector<ItemInfo> itemInfos;
public:
	void InitItemInfo();
	inline ItemInfo GetItemInfo(int idx) { return itemInfos[idx]; }
};

