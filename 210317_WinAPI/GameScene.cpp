#include "GameScene.h"
#include "KeyManager.h"
#include "Image.h"
#include "Stage.h"
#include "Player.h"
#include "StageObject.h"
#include "Camera.h"
#include "InventoryContainer.h"
#include "Inventory.h"
#include "UIInventory.h"
#include "GameData.h"
#include "CommonFunction.h"

HRESULT GameScene::Init()
{
	SetClientRect(g_hWnd, GAMESCENESIZE_X, GAMESCENESIZE_Y);

	GameData::GetSingleton()->InitItemInfo();

	Camera* cam = Camera::GetSingleton();
	cam->SetScreenSize(POINT{ GAMESCENESIZE_X , GAMESCENESIZE_Y });
	cam->SetScale(1.5f);

	stage = new Stage();
	stage->Init(POINT{ Con::TILESIZE, Con::TILESIZE });
	stage->Load();

	player = new Player();
	player->Init();

	inventoryContainer = new InventoryContainer();
	inventoryContainer->Init();

	uiInventory = new UIInventory();
	uiInventory->Init();
	uiInventory->SetInventory(inventoryContainer->GetPlayerInventory());

	camPos = player->GetPos();

	return S_OK;
}

void GameScene::Release()
{
	SAFE_RELEASE(stage);
	SAFE_RELEASE(player);
	SAFE_RELEASE(inventoryContainer);
	SAFE_RELEASE(uiInventory);
}

void GameScene::Update()
{
	Camera* cam = Camera::GetSingleton();
	FPOINT worldMouse = cam->CameraToWorld(toFpoint(g_ptMouse));
	if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
	{
		cam->SetScale(cam->GetScale() - 1.0f * TimerManager::GetSingleton()->GetElapsedTime());
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('X'))
	{
		cam->SetScale(cam->GetScale() + 1.0f * TimerManager::GetSingleton()->GetElapsedTime());
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		POINT selTile = stage->PosToTile(worldMouse);
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
	if (inventoryContainer
		&& inventoryContainer->GetPlayerInventory())
	{
		bool shiftDown = KeyManager::GetSingleton()->IsStayKeyDown(VK_LSHIFT);
		int itemNum = 0;
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown('1')) { itemNum = 1; }
			if (KeyManager::GetSingleton()->IsOnceKeyDown('2')) { itemNum = 2; }
			if (KeyManager::GetSingleton()->IsOnceKeyDown('3')) { itemNum = 3; }
			if (KeyManager::GetSingleton()->IsOnceKeyDown('4')) { itemNum = 4; }
		}
		
		if(itemNum != 0)
		{
			if (shiftDown)
			{
				inventoryContainer->GetPlayerInventory()->RemoveItem(Inventory::Item{ itemNum, 1 });
			}
			else
			{
				inventoryContainer->GetPlayerInventory()->AddItem(Inventory::Item{ itemNum, 1 });
			}
		}
	}
	if (uiInventory)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_TAB))
		{
			uiInventory->SetActive(!uiInventory->GetActive());
		}
	}

	stage->Update();
	player->Update();
	CheckCollision();
	
}

void GameScene::Render(HDC hdc)
{
	SetCamera();
	PatBlt(hdc, 0, 0,
		GAMESCENESIZE_X, GAMESCENESIZE_X, WHITENESS);
	stage->Render(hdc);
	player->Render(hdc);
	uiInventory->Render(hdc);
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

void GameScene::SetCamera()
{
	float mouseFollowScale = Con::CAM_MOUSE_FOLLOW_SCALE;
	float smoothSpeed = 
		Con::CAM_SMOOTH_SPEED * TimerManager::GetSingleton()->GetElapsedTime();
	Camera* cam = Camera::GetSingleton();
	FPOINT mouseWorldPos =
		cam->CameraToWorld(FPOINT{ (float)g_ptMouse.x, (float)g_ptMouse.y });
	FPOINT targetPos = FPOINT{
		player->GetPos().x * (1 - mouseFollowScale) +
		mouseWorldPos.x * mouseFollowScale,
		player->GetPos().y * (1 - mouseFollowScale) +
		mouseWorldPos.y * mouseFollowScale };
	camPos = FPOINT{
		camPos.x * (1 - smoothSpeed) + targetPos.x * smoothSpeed,
		camPos.y * (1 - smoothSpeed) + targetPos.y * smoothSpeed,
	};
	cam->SetPosCenter(camPos);
}
