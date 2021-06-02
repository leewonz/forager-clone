#pragma once
#include "config.h"
#include "GameData.h"

class Inventory;
class InventoryContainer
{
private:
	Inventory* playerInventory;
	Inventory* equipInventory;
	Inventory* vaultInventory[Con::INVEN_VAULT_COUNT];

public:
	HRESULT Init();
	void Release();

	void AddDropItem(Item item);
	int GetItemCount(int idx);
	void RemoveItem(Item item);

	inline Inventory* GetPlayerInventory() {return playerInventory; }
	inline Inventory* GetEquipInventory() {return equipInventory; }
	inline Inventory* GetVaultInventory(int idx) {return vaultInventory[idx]; }
};

