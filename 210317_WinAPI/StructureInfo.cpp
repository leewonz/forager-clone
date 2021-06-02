#include "StructureInfo.h"

void StructureInfo::Init(int typeIndex, string codename, string name)
{
	img = ImageManager::GetSingleton()->FindImage("structure_" + codename);
	this->typeIdx = typeIndex;
	this->codename = codename;
	this->name = name;
	this->tileSize = POINT{ 1, 1 };
	//fill_n(drops, Con::RESOURCE_DROP_MAX, Item{0, 0});
}

void StructureInfo::AddDrop(Item item) 
{
	if (item.idx > 0) { drops.push_back(item); } 
	else 
	{
		string msg = codename + " / Structure 드롭 아이템 지정 실패 (StructureInfo.cpp)";
		MessageBox(g_hWnd, msg.c_str(), "실패", MB_OK);
	}
}
