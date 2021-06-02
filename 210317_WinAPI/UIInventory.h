#pragma once
#include "UIObject.h"
class Image;
class Inventory;
class UIInventory :
    public UIObject
{
private:
	struct Slot
	{
		int idx;
		RECT box;
	};

	const POINT startPos = { 128, 196 };

    Inventory* inventory;
	char szText[128] = "";

	POINT slotGridCount = {0, 0};
	vector<Slot> slots;

	Image* inventorySlotImg;
	Image* inventorySlotSelectionImg;
	const int SLOT_IMG_OFFSET = -12;

	bool isDragging = false;
	int draggingSlot = -1;
	int selectedSlot = 0;

public:
	HRESULT Init(POINT gridCount);

	inline void SetInventory(Inventory* inventory) { this->inventory = inventory; }
	inline Inventory* GetInventory() { return inventory; }

	virtual pair<UI_MESSAGE, int> MouseDown(POINT mousePos);
	virtual pair<UI_MESSAGE, int> MouseUp(POINT mousePos);
	virtual pair<UI_MESSAGE, int> Back();
	virtual void OnActivate();
	virtual void OnDeactivate();

	void Render(HDC hdc);
};

