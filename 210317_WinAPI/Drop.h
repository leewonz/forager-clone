#pragma once
#include "StageObject.h"
#include "Inventory.h"
#include "GameData.h"
class Drop : public StageObject
{
private:
	const float SIZE = 24;
	const float ANIM_SPEED = 3.0f;
	const float ANIM_JUMP_HEIGHT = 15.0f;

	GameNode* scene;
	Item item;
	float initTime = 0.0f;

	FPOINT animStartPos = FPOINT{0.0f, 0.0f};
	float animProgress = 0.0f;
public:
	HRESULT Init();
	void Update();
	void Release();
	void Render(HDC hdc);
	void SetAnimationStartPos(FPOINT animStartPos);
	inline GameNode* GetScene() { return scene; };
	inline void SetScene(GameNode* scene) { this->scene = scene; };
	inline void SetItem(Item item) { this->item = item; }
	inline Item GetItem() { return this->item; }
	inline bool IsAnimationEnded() { return animProgress > 0.99f; }
};

