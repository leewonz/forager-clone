#include "InventoryContainer.h"
#include "Inventory.h"
HRESULT InventoryContainer::Init()
{
	playerInventory = new Inventory();
	playerInventory->Init(this, Con::INVEN_PLAYER_X * Con::INVEN_PLAYER_Y);
	for (int i = 0; i < Con::INVEN_VAULT_COUNT; i++)
	{
		vaultInventory[i] = new Inventory();
		vaultInventory[i]->Init(this, Con::INVEN_VAULT_X * Con::INVEN_VAULT_Y);
	}

	return S_OK;
}
void InventoryContainer::Release()
{
	SAFE_RELEASE(playerInventory);
	for (int i = 0; i < Con::INVEN_VAULT_COUNT; i++)
	{
		SAFE_RELEASE(vaultInventory[i]);
	}
}