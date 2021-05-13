#include "GameScene.h"
#include "KeyManager.h"
#include "Image.h"
#include "Stage.h"

HRESULT GameScene::Init()
{
	stage = new Stage();
	stage->Init(POINT{ TILESIZE, TILESIZE });
	stage->Load();
	return S_OK;
}

void GameScene::Release()
{
	SAFE_RELEASE(stage);
}

void GameScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		POINT selTile = stage->PosToTile(g_ptMouse);
		if (stage->CanBuild(RECT{ selTile.x, selTile.y, selTile.x, selTile.y }))
		{
			stage->BuildStructure(selTile, 0);
		}
	}
	stage->Update();
	//CheckCollision();
}

void GameScene::Render(HDC hdc)
{
	stage->Render(hdc);
}
