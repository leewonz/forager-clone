#include "UIInventory.h"
#include "Inventory.h"
#include "InventoryContainer.h"
#include "Image.h"
#include "GameData.h"
#include "CommonFunction.h"

HRESULT UIInventory::Init(POINT gridCount)
{
	pos.x = startPos.x;
	pos.y = startPos.y;
	size = FPOINT{ GAMESCENESIZE_X, GAMESCENESIZE_Y };
	

	this->slotGridCount = gridCount;
	for (int i = 0; i < slotGridCount.x * slotGridCount.y; i++)
	{
		int gridX = i % slotGridCount.x;
		int gridY = i / slotGridCount.x;
		RECT slotRect = RECT
		{
			(64 + 32) * gridX,
			(64 + 32) * gridY,
			(64 + 32) * gridX + 64,
			(64 + 32) * gridY + 64
		};
		Slot slot = Slot{ i, slotRect };
		slots.push_back(slot);
	}

	inventorySlotImg = 
		ImageManager::GetSingleton()->FindImage("ui_inventorySlot");
	inventorySlotSelectionImg = 
		ImageManager::GetSingleton()->FindImage("ui_inventorySlotSelection");
	bgImg = 
		ImageManager::GetSingleton()->FindImage("ui_textBoxShort");

	return S_OK;
}

pair<UI_MESSAGE, int> UIInventory::MouseDown(POINT mousePos)
{
	if (isActive && inventory)
	{
		for (int i = 0; i < slotGridCount.x * slotGridCount.y; i++)
		{
			Slot slot = slots[i];
			RECT slotRect = RECT{ slot.box.left + (int)pos.x, slot.box.top + (int)pos.y,
							 slot.box.right + (int)pos.x, slot.box.bottom + (int)pos.y };

			if (PointInRect(mousePos, slotRect))
			{
				isDragging = true;
				draggingSlot = i;
				selectedSlot = i;
				return { UI_MESSAGE::OK, i };
			}
		}
		if (PointInRect(mousePos, RECT{ 0, 0, (LONG)size.x, (LONG)size.y }))
		{
			return { UI_MESSAGE::BLOCKED, 0 };
		}
		return {UI_MESSAGE::BLOCKED, 0};
	}
	else
	{
		return { UI_MESSAGE::NONE, 0 };
	}
}

pair<UI_MESSAGE, int> UIInventory::MouseUp(POINT mousePos)
{
	if (isActive && inventory)
	{
		for (int upSlot = 0; upSlot < slotGridCount.x * slotGridCount.y; upSlot++)
		{
			Slot slot = slots[upSlot];
			RECT slotRect = RECT{ slot.box.left + (int)pos.x, slot.box.top + (int)pos.y,
							 slot.box.right + (int)pos.x, slot.box.bottom + (int)pos.y };

			if (PointInRect(mousePos, slotRect))
			{
				selectedSlot = upSlot;
				if (isDragging)
				{
					Item itemOld = inventory->RemoveItem(draggingSlot);
					Item itemNew = inventory->RemoveItem(upSlot);
					if (itemOld.idx == itemNew.idx)
					{
						inventory->AddItem(itemOld, upSlot);
						inventory->AddItem(itemNew, upSlot);
					}
					else
					{
						inventory->AddItem(itemOld, upSlot);
						inventory->AddItem(itemNew, draggingSlot);
					}
				}
				//if (inventory->GetItem(draggingSlot).idx != 0 &&
				//	inventory->GetItem(upSlot).idx != 0)
				//{

				//}

				isDragging = false;
				draggingSlot = -1;

				return { UI_MESSAGE::OK, upSlot };
			}
		}
		return { UI_MESSAGE::BLOCKED, 0 };
	}
	else
	{
		return { UI_MESSAGE::NONE, 0 };
	}
}

pair<UI_MESSAGE, int> UIInventory::Back()
{
	return { UI_MESSAGE::NONE, 0 };
}

void UIInventory::OnActivate()
{
	isDragging = false;
	draggingSlot = -1;
}

void UIInventory::OnDeactivate()
{
	isDragging = false;
	draggingSlot = -1;
}

void UIInventory::Render(HDC hdc)
{
	float currTime = TimerManager::GetSingleton()->GetProgramTime();
	if (isActive && inventory)
	{
		//Rectangle(hdc, 0, 0, 100, 100);
		Item item;
		ItemInfo* info;

		for (int i = 0; i < slotGridCount.x * slotGridCount.y; i++)
		{
			Slot slot = slots[i];
			RECT slotRect = RECT{ slot.box.left + (int)pos.x, slot.box.top + (int)pos.y,
							 slot.box.right + (int)pos.x, slot.box.bottom + (int)pos.y };

			item = inventory->GetItem(i);
			info = GameData::GetSingleton()->GetItemInfo(item.idx);

			inventorySlotImg->Render(
				hdc, slotRect.left + SLOT_IMG_OFFSET, slotRect.top + SLOT_IMG_OFFSET, 4.0f, false);
			//Rectangle(hdc, slotRect.left, slotRect.top, slotRect.right, slotRect.bottom);

			if (selectedSlot == i)
			{
				inventorySlotSelectionImg->FrameRender(
					hdc, slotRect.left + SLOT_IMG_OFFSET, slotRect.top + SLOT_IMG_OFFSET,
					(int)(currTime * 10.0f) % inventorySlotSelectionImg->GetImageInfo()->maxFrameX, 0, false, 1.0f);
			}

			info->img->Render(hdc, slotRect.left, slotRect.top, 2.0f, false);
			wsprintf(szText, "%d", item.count);
			TextOut(hdc, slotRect.left, slotRect.top + 48, szText, strlen(szText));
			//wsprintf(szText, info->name.c_str());
			//TextOut(hdc, slotRect.left, slotRect.top + 65, szText, strlen(szText));
		}

		item = inventory->GetItem(draggingSlot);
		if (draggingSlot >= 0 && draggingSlot < inventory->GetSize())
		{
			info = GameData::GetSingleton()->GetItemInfo(item.idx);
			info->img->Render(hdc, g_ptMouse.x, g_ptMouse.y, 2.0f, true);
		}

		bgImg->Render(hdc, pos.x + 800, pos.y, 1.0f, false);
		item = inventory->GetItem(selectedSlot);
		info = GameData::GetSingleton()->GetItemInfo(item.idx);
		if (item.idx != GameData::EMPTY_ITEM.idx)
		{
			info->img->Render(hdc, pos.x + 800 + 8, pos.y + 8, 2.0f, false);
			wsprintf(szText, "%s", info->name.c_str());
			TextOut(hdc, pos.x + 800 + 8 + 64 + 4, pos.y + 48, szText, strlen(szText));
			wsprintf(szText, "°³¼ö: %d", item.count);
			TextOut(hdc, pos.x + 800 + 16, pos.y + 96, szText, strlen(szText));
		}
	}
}
