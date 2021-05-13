#include "GameScene.h"
#include "KeyManager.h"
#include "Image.h"
#include "Stage.h"
#include "Player.h"

HRESULT GameScene::Init()
{
	stage = new Stage();
	stage->Init(POINT{ TILESIZE, TILESIZE });
	stage->Load();

	player = new Player();
	player->Init();
	player->SetPos(FPOINT{100, 100});

	return S_OK;
}

void GameScene::Release()
{
	SAFE_RELEASE(stage);
	SAFE_RELEASE(player);
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
	if (player)
	{
		FPOINT moveDir = FPOINT{ 0.0f, 0.0f };
		if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
		{
			moveDir.y -= 1;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
		{
			moveDir.y += 1;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			moveDir.x -= 1;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			moveDir.x += 1;
		}
		player->Move(moveDir);
	}
	stage->Update();
	player->Update();
	//CheckCollision();
}

void GameScene::Render(HDC hdc)
{
	stage->Render(hdc);
	player->Render(hdc);
}
