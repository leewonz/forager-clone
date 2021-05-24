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
	static const Item EMPTY_ITEM;

	HRESULT Init(InventoryContainer* container, int size);
	void Release();
	// Ư�� ������ �߰�
	bool AddItem(Item item);
	// Ư�� ���Կ� Ư�� ������ �߰�
	bool AddItem(Item item, int slot);
	// Ư�� ������ ����
	bool RemoveItem(Item item);
	// Ư�� ���Կ� �ִ� � �������̵� ����
	Item RemoveItem(int slot, int count);
	// Ư�� ���Կ� �ִ� � �������̵� ����
	Item RemoveItem(int slot);
	// ������ ��ȯ
	Item GetItem(int slot);
	// ������ ��ġ ��ȯ
	int FindItem(int idx);

	inline int GetSize() { return size; }
	inline InventoryContainer* GetContainer() { return container; }
	inline void SetContainer(InventoryContainer* container) { this->container = container; }
	inline bool IsEmpty(Item item) { return item.idx == 0; }
};

