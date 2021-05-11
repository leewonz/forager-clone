#include "BattleScene.h"
#include "Image.h"
#include "Stage.h"

HRESULT BattleScene::Init()
{
	stage = new Stage();
	stage->Init(POINT{ TILESIZE, TILESIZE });
	stage->Load();
	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(stage);
}

void BattleScene::Update()
{
	stage->Update();
	//CheckCollision();
}

void BattleScene::Render(HDC hdc)
{
	stage->Render(hdc);
}
