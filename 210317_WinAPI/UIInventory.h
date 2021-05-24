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

	// ���õ� ���� ��� ��ȯ. ���õ� �� ������ nullptr ��ȯ.
	virtual pair<UI_MESSAGE, int> MouseDown(POINT mousePos);
	// ���õ� ���� ��� ��ȯ. ���õ� �� ������ nullptr ��ȯ.
	virtual pair<UI_MESSAGE, int> MouseUp(POINT mousePos);
	// SetActive�� �ڽ��� ������ �� ȣ��
	virtual void OnActivate();
	// SetActive�� �ڽ��� ������ �� ȣ��
	virtual void OnDeactivate();

	void Render(HDC hdc);
};

