#pragma once
#include "config.h"
#include "GameData.h"

class InventoryContainer;

class Inventory
{
public:

private:
	vector<Item> items;
	int size;
	InventoryContainer* container;

public:
	HRESULT Init(InventoryContainer* container, int size);
	void Release();
	// 특정 아이템 추가
	bool AddItem(Item item);
	// 특정 슬롯에 특정 아이템 추가
	bool AddItem(Item item, int slot);
	// 특정 아이템 삭제
	bool RemoveItem(Item item);
	// 특정 슬롯에 있는 어떤 아이템이든 삭제
	Item RemoveItem(int slot, int count);
	// 특정 슬롯에 있는 어떤 아이템이든 삭제
	Item RemoveItem(int slot);
	// 특정 슬롯에 있는 아이템 반환
	Item GetItem(int slot);
	// 특정 아이템의 개수 반환
	int GetItemCount(int idx);
	// 아이템 위치 반환
	int FindItem(int idx);

	inline int GetSize() { return size; }
	inline InventoryContainer* GetContainer() { return container; }
	inline void SetContainer(InventoryContainer* container) { this->container = container; }
	inline bool IsEmpty(Item item) { return item.idx == 0; }
};

