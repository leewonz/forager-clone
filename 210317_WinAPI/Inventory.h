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
	// Ư�� ������ �߰�
	bool AddItem(Item item);
	// Ư�� ���Կ� Ư�� ������ �߰�
	bool AddItem(Item item, int slot);
	// Ư�� ������ ����
	bool RemoveItem(Item item);
	// Ư�� ���Կ� �ִ� � �������̵� ����
	bool RemoveItem(int slot, int count);
	// ������ ��ȯ
	Item GetItem(int slot);
	// ������ ��ġ ��ȯ
	int FindItem(int idx);

	inline int GetCapacity() { return capacity; }
	inline InventoryContainer* GetContainer() { return container; }
	inline void SetContainer(InventoryContainer* container) { this->container = container; }
};

