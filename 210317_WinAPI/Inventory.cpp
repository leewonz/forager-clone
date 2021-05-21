#include "Inventory.h"

HRESULT Inventory::Init(InventoryContainer* container, int capacity)
{
	SetContainer(container);
	this->capacity = capacity;
	return S_OK;
}

void Inventory::Release()
{
	container = nullptr;
}

bool Inventory::AddItem(Item item)
{
	vector<Item>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++)
	{
		if (iter->idx == item.idx)
		{
			iter->count += item.count;
			return true;
		}
	}
	if (items.size() == capacity)
	{
		return false;
	}
	else
	{
		items.push_back(item);
		return true;
	}
}

bool Inventory::AddItem(Item item, int slot)
{
	if (slot < items.size() && items[slot].idx == item.idx)
	{
		items[slot].count += item.count;
		return true;
	}
	else
	{
		return false;
	}
}

bool Inventory::RemoveItem(Item item)
{
	vector<Item>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++)
	{
		if (iter->idx == item.idx)
		{
			if (iter->count > item.count)
			{
				iter->count -= item.count;
			}
			else if (iter->count == item.count)
			{
				items.erase(iter);
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

bool Inventory::RemoveItem(int slot, int count)
{
	if (items[slot].idx == items[slot].idx)
	{
		if (items[slot].count > count)
		{
			items[slot].count -= count;
		}
		else if (items[slot].count == count)
		{
			items.erase(items.begin() + slot);
		}
		else
		{
			return false;
		}
	}
	return true;
}

Inventory::Item Inventory::GetItem(int slot)
{
	if (slot < items.size())
	{
		return items[slot];
	}
	else
	{
		return Item{ 0, 0 };
	}
}

int Inventory::FindItem(int idx)
{
	vector<Item>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++)
	{
		if (iter->idx == idx)
		{
			return iter - items.begin();
		}
	}
	return -1;
}
