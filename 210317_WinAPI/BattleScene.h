#pragma once
#include "GameNode.h"

// ���� MainGame Ŭ������ ������ �̵�

class Stage;
class Image;
class BattleScene : public GameNode
{
private:
	Stage* stage;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~BattleScene() {};
};

