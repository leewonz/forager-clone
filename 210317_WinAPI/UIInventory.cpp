#include "UIInventory.h"
#include "Inventory.h"
#include "InventoryContainer.h"
#include "Image.h"
#include "GameData.h"

pair<UI_MESSAGE, int> UIInventory::MouseDown(POINT pos)
{
	return {UI_MESSAGE::NONE, 0};
}

pair<UI_MESSAGE, int> UIInventory::MouseUp(POINT pos)
{
	return {UI_MESSAGE::NONE, 0};
}

void UIInventory::OnActivate()
{
}

void UIInventory::OnDeactivate()
{
}

void UIInventory::Render(HDC hdc)
{
	if (isActive)
	{
		Rectangle(hdc, 0, 0, 100, 100);
		InventoryContainer* container = inventory->GetContainer();
		for (int i = 0; i < inventory->GetCapacity(); i++)
		{
			int x = i % Con::INVEN_PLAYER_X;
			int y = i / Con::INVEN_PLAYER_X;

			Inventory::Item item = inventory->GetItem(i);
			ItemInfo info = GameData::GetSingleton()->GetItemInfo(item.idx);

			info.img->Render(hdc, (x + 1) * 100, (y + 1) * 100, false);
			wsprintf(szText, "%d", item.count);
			TextOut(hdc, (x + 1) * 100, (y + 1) * 100 + 20, szText, strlen(szText));
			wsprintf(szText, info.name.c_str());
			TextOut(hdc, (x + 1) * 100, (y + 1) * 100 + 40, szText, strlen(szText));
		}
	}
}
