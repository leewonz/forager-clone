#pragma once
#include "StageObject.h"
#include "Inventory.h"
#include "GameData.h"
class Drop : public StageObject
{
private:
	GameNode* scene;
	const float SIZE = 24;
	Item item;
	float initTime = 0.0f;
public:
	HRESULT Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	inline GameNode* GetScene() { return scene; };
	inline void SetScene(GameNode* scene) { this->scene = scene; };
	inline void SetItem(Item item) { this->item = item; }
	inline Item GetItem() { return this->item; }
};

