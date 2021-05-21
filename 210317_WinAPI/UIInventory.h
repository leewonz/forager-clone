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

	// 선택된 리프 노드 반환. 선택된 게 없으면 nullptr 반환.
	virtual pair<UI_MESSAGE, int> MouseDown(POINT pos);
	// 선택된 리프 노드 반환. 선택된 게 없으면 nullptr 반환.
	virtual pair<UI_MESSAGE, int> MouseUp(POINT pos);
	// SetActive로 자신이 켜졌을 때 호출
	virtual void OnActivate();
	// SetActive로 자신이 꺼졌을 때 호출
	virtual void OnDeactivate();

	void Render(HDC hdc);
};

