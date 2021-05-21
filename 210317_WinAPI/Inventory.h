#pragma once
#include "config.h"

class InventoryContainer;

class Inventory
{
public:
	struct Item
	{
		int idx;
		int count;
	};

private:
	vector<Item> items;
	int capacity;
	InventoryContainer* container;

public:
	HRESULT Init(InventoryContainer* container, int capacity);
	void Release();
	// 특정 아이템 추가
	bool AddItem(Item item);
	// 특정 슬롯에 특정 아이템 추가
	bool AddItem(Item item, int slot);
	// 특정 아이템 삭제
	bool RemoveItem(Item item);
	// 특정 슬롯에 있는 어떤 아이템이든 삭제
	bool RemoveItem(int slot, int count);
	// 아이템 반환
	Item GetItem(int slot);
	// 아이템 위치 반환
	int FindItem(int idx);

	inline int GetCapacity() { return capacity; }
	inline InventoryContainer* GetContainer() { return container; }
	inline void SetContainer(InventoryContainer* container) { this->container = container; }
};

