#pragma once
#include "UIObject.h"
class Inventory;
class UIInventory :
    public UIObject
{
private:
    Inventory* inventory;
	char szText[128] = "";
public:
	inline void SetInventory(Inventory* inventory) { this->inventory = inventory; }
	inline Inventory* GetInventory() { return inventory; }

	// ���õ� ���� ��� ��ȯ. ���õ� �� ������ nullptr ��ȯ.
	virtual pair<UI_MESSAGE, int> MouseDown(POINT pos);
	// ���õ� ���� ��� ��ȯ. ���õ� �� ������ nullptr ��ȯ.
	virtual pair<UI_MESSAGE, int> MouseUp(POINT pos);
	// SetActive�� �ڽ��� ������ �� ȣ��
	virtual void OnActivate();
	// SetActive�� �ڽ��� ������ �� ȣ��
	virtual void OnDeactivate();

	void Render(HDC hdc);
};

