#pragma once
#include "StageObject.h"
#include "Inventory.h"
#include "GameData.h"
class Drop : public StageObject
{
private:
	const float SIZE = 20;
	Item item;
public:
	HRESULT Init();
	void Update();
	void Release();
	void Render(HDC hdc);
	inline void SetItem(Item item) { this->item = item; }
	inline Item GetItem() { return this->item; }
};

