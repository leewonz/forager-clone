#pragma once
#include "config.h"

class Inventory;
class InventoryContainer
{
private:
	Inventory* playerInventory;
	Inventory* vaultInventory[Con::INVEN_VAULT_COUNT];

public:
	HRESULT Init();
	void Release();
	inline Inventory* GetPlayerInventory() {return playerInventory; }
	inline Inventory* GetVaultInventory(int idx) {return vaultInventory[idx]; }
};

