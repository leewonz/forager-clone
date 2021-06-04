#include "Inventory.h"
#include <algorithm>

HRESULT Inventory::Init(InventoryContainer* container, int size)
{
	SetContainer(container);
	this->size = size;
	items.resize(this->size);
	fill(items.begin(), items.end(), GameData::EMPTY_ITEM);
	return S_OK;
}

void Inventory::Release()
{
	container = nullptr;
}

bool Inventory::AddItem(Item item)
{
	vector<Item>::iterator iter, iterFirstEmpty;
	bool isEmptyFound = false;

	iter = iterFirstEmpty = items.begin();
	for (iter = items.begin(); iter != items.end(); ++iter)
	{
		if (iter->idx == item.idx)
		{
			iter->count += item.count;
			return true;
		}
		else if (IsEmpty(*iter) && !isEmptyFound)
		{
			isEmptyFound = true;
			iterFirstEmpty = iter;
		}
	}

	if (isEmptyFound)
	{
		*iterFirstEmpty = item;
		return true;
	}

	return false;
}

bool Inventory::AddItem(Item item, int slot)
{
	int temp = 0;
	if (slot < items.size())
	{
		if (items[slot].idx == item.idx)
		{
			items[slot].count += item.count;
			return true;
		}
		else if (IsEmpty(items[slot]))
		{
			items[slot] = item;
			return true;
		}
	}

	return false;
}

bool Inventory::RemoveItem(Item item)
{
	vector<Item>::iterator iter;
	for (iter = items.begin(); iter != items.end(); ++iter)
	{
		if (iter->idx == item.idx)
		{
			if (iter->count > item.count)
			{
				iter->count -= item.count;
				return true;
			}
			else if (iter->count == item.count)
			{
				*iter = GameData::EMPTY_ITEM;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

Item Inventory::RemoveItem(int slot, int count)
{
	if (slot < items.size())
	{
		Item item = items[slot];
		if (item.count > count)
		{
			items[slot].count -= count;
			return Item{ item.idx, count };
		}
		else if (item.count == count)
		{
			items[slot] = GameData::EMPTY_ITEM;
			return Item{ item.idx, count };
		}
		else
		{
			return GameData::EMPTY_ITEM;
		}
	}
	return GameData::EMPTY_ITEM;
}

Item Inventory::RemoveItem(int slot)
{
	if (slot < items.size())
	{
		Item item = items[slot];
		items[slot] = GameData::EMPTY_ITEM;
		return item;
	}
	return GameData::EMPTY_ITEM;
}

Item Inventory::GetItem(int slot)
{
	if (slot < items.size())
	{
		return items[slot];
	}
	else
	{
		return GameData::EMPTY_ITEM;
	}
}

int Inventory::GetItemCount(int idx)
{
	vector<Item>::iterator iter;

	iter = items.begin();
	for (iter = items.begin(); iter != items.end(); ++iter)
	{
		if (iter->idx == idx)
		{
			return iter->count;
		}
	}
	return 0;
}

int Inventory::FindItem(int idx)
{
	vector<Item>::iterator iter;
	for (iter = items.begin(); iter != items.end(); ++iter)
	{
		if (iter->idx == idx)
		{
			return iter - items.begin();
		}
	}
	return -1;
}
