#pragma once
#include "GameNode.h"

// ���� MainGame Ŭ������ ������ �̵�

class Stage;
class StageObject;
class Image;
class Player;
class UIInventory;
class InventoryContainer;
class GameScene : public GameNode
{
private:
	Stage* stage;
	Player* player;
	UIInventory* uiInventory;
	InventoryContainer* inventoryContainer;

	FPOINT camPos;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckCollision();
	void CollisionPush(StageObject* movable, StageObject* immovable);
	void SetCamera();

	virtual ~GameScene() {};
};

