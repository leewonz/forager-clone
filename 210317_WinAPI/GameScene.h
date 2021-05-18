#pragma once
#include "GameNode.h"

// ���� MainGame Ŭ������ ������ �̵�

class Stage;
class StageObject;
class Image;
class Player;
class GameScene : public GameNode
{
private:
	Stage* stage;
	Player* player;

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

