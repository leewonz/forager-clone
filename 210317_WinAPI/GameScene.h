#pragma once
#include "GameNode.h"

// 기존 MainGame 클래스의 내용을 이동

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

