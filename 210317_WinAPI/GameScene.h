#pragma once
#include "GameNode.h"

// ���� MainGame Ŭ������ ������ �̵�

class Stage;
class Image;
class Player;
class GameScene : public GameNode
{
private:
	Stage* stage;
	Player* player;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~GameScene() {};
};

