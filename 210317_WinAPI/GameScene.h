#pragma once
#include "GameNode.h"

// 기존 MainGame 클래스의 내용을 이동

class Stage;
class StageObject;
class Image;
class Player;
class UIInventory;
class InventoryContainer;
class DropContainer;
class GameScene : public GameNode
{
private:
	Stage* stage;
	Player* player;
	UIInventory* uiInventory;
	InventoryContainer* inventoryContainer;
	DropContainer* dropContainer;

	FPOINT camPos;

	float sceneTime;
	float gameTime;
	float lastResourceRegenTime;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void InitTimes();
	void UpdateTimes();
	void CheckCollision();
	void CheckCollisionPlayerAndItem();
	void CollisionPush(StageObject* movable, StageObject* immovable);
	bool CheckIfColliding(StageObject* obj1, StageObject* obj2);
	void SetCamera();

	virtual ~GameScene() {};
};

