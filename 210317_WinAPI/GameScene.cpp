#include "GameScene.h"
#include "KeyManager.h"
#include "Image.h"
#include "Stage.h"
#include "Player.h"
#include "StageObject.h"

HRESULT GameScene::Init()
{
	stage = new Stage();
	stage->Init(POINT{ Con::TILESIZE, Con::TILESIZE });
	stage->Load();

	player = new Player();
	player->Init();
	player->SetPos(FPOINT{100, 100});
	player->SetOffset(FPOINT{-10, -10});
	player->SetSize(FPOINT{20, 20});

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
	CheckCollision();
}

void GameScene::Render(HDC hdc)
{
	stage->Render(hdc);
	player->Render(hdc);
}

void GameScene::CheckCollision()
{
	int tileCheckRange = 3;
	// 플레이어 - 타일
	POINT plTilePos = stage->PosToTile(player->GetPos());
	RECT plCheckRegion = RECT{
		max(plTilePos.x - tileCheckRange, 0),
		max(plTilePos.y - tileCheckRange, 0),
		min(plTilePos.x + tileCheckRange, Con::TILE_X - 1),
		min(plTilePos.y + tileCheckRange, Con::TILE_Y - 1)
	};
	for (int y = plCheckRegion.top; y <= plCheckRegion.bottom; y++)
	{
		for (int x = plCheckRegion.left; x <= plCheckRegion.right; x++)
		{
			Terrain* currTerrain = stage->GetTerrain(POINT{ x, y });
			if (!currTerrain->GetIsLand()) 
			{
				CollisionPush(player, currTerrain);
			}

			StageObject* currStructure = (StageObject*)currTerrain->GetStructure();
			if (currStructure)
			{
				CollisionPush(player, currStructure);
			}
		}
	}
}

void GameScene::CollisionPush(StageObject* movable, StageObject* immovable)
{
	RECT* resultRect = new RECT{ 0, 0, 0, 0 };
	FPOINT plPos = movable->GetPos();
	RECT* plRect = &movable->GetBox();
	RECT* tileRect = &immovable->GetBox();

	if (IntersectRect(resultRect,
		plRect,
		tileRect))
	{
		POINT resultSize = POINT{
			resultRect->right - resultRect->left,
			resultRect->bottom - resultRect->top
		};
		if (resultSize.x < resultSize.y)
		{
			float moveAmt =
				resultSize.x *
				((plPos.x < immovable->GetPos().x) ? -1.0f : 1.0f);
			movable->SetPos(FPOINT{ plPos.x + moveAmt, plPos.y });
		}
		else
		{
			float moveAmt =
				resultSize.y *
				((plPos.y < immovable->GetPos().y) ? -1.0f : 1.0f);
			movable->SetPos(FPOINT{ plPos.x, plPos.y + moveAmt });
		}
	}

	SAFE_DELETE(resultRect);
}
