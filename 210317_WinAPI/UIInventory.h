#pragma once
#include "UIObject.h"
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

    Inventory* inventory;
	char szText[128] = "";

	POINT slotGridCount = {0, 0};
	vector<Slot> slots;

	bool isDragging = false;
	int draggingSlot = -1;

public:
	HRESULT Init(POINT gridCount);

	inline void SetInventory(Inventory* inventory) { this->inventory = inventory; }
	inline Inventory* GetInventory() { return inventory; }

	// 선택된 리프 노드 반환. 선택된 게 없으면 nullptr 반환.
	virtual pair<UI_MESSAGE, int> MouseDown(POINT mousePos);
	// 선택된 리프 노드 반환. 선택된 게 없으면 nullptr 반환.
	virtual pair<UI_MESSAGE, int> MouseUp(POINT mousePos);
	// SetActive로 자신이 켜졌을 때 호출
	virtual void OnActivate();
	// SetActive로 자신이 꺼졌을 때 호출
	virtual void OnDeactivate();

	void Render(HDC hdc);
};

