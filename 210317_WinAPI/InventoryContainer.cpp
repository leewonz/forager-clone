#include "InventoryContainer.h"
#include "Inventory.h"
HRESULT InventoryContainer::Init()
{
	playerInventory = new Inventory();
	playerInventory->Init(this, Con::INVEN_PLAYER_X * Con::INVEN_PLAYER_Y);

	equipInventory = new Inventory();
	equipInventory->Init(this, Con::INVEN_EQUIP_X * Con::INVEN_EQUIP_Y);

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

void InventoryContainer::AddDropItem(Item item)
{
	switch (GameData::GetSingleton()->GetItemInfo(item.idx)->category)
	{
	case ItemCategory::COIN:
		equipInventory->AddItem(item, 0);
		break;
	case ItemCategory::PICKAXE:
		equipInventory->AddItem(item, 1);
		break;
	case ItemCategory::SHOVEL:
		equipInventory->AddItem(item, 2);
		break;
	case ItemCategory::SWORD:
		equipInventory->AddItem(item, 3);
		break;
	default:
		playerInventory->AddItem(item);
		break;
	}
}

int InventoryContainer::GetItemCount(int idx)
{
	int itemCount = 0;
	itemCount += playerInventory->GetItemCount(idx);
	//for (int i = 0; i < Con::INVEN_VAULT_COUNT; i++)
	//{
	//	itemCount += vaultInventory[i]->GetItemCount(idx);
	//}
	itemCount += equipInventory->GetItemCount(idx);
	return itemCount;
}

void InventoryContainer::RemoveItem(Item item)
{
	Item itemToRemove = item;
	playerInventory->RemoveItem(itemToRemove);
}
