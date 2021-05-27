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
#include "DropContainer.h"
#include "Drop.h"
#include "GameData.h"
#include "StructureInfo.h"
#include "config.h"
#include "CommonFunction.h"

HRESULT GameScene::Init()
{
	SetClientRect(g_hWnd, GAMESCENESIZE_X, GAMESCENESIZE_Y);

	InitTimes();

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

	dropContainer = new DropContainer();
	dropContainer->Init();

	uiInventory = new UIInventory();
	uiInventory->Init(POINT{ Con::INVEN_PLAYER_X, Con::INVEN_PLAYER_Y });
	uiInventory->SetInventory(inventoryContainer->GetPlayerInventory());

	camPos = player->GetPos();

	return S_OK;
}

void GameScene::Release()
{
	SAFE_RELEASE(stage);
	SAFE_RELEASE(player);
	SAFE_RELEASE(inventoryContainer);
	SAFE_RELEASE(dropContainer);
	SAFE_RELEASE(uiInventory);
}

void GameScene::Update()
{
	Camera* cam = Camera::GetSingleton();
	FPOINT worldMouse = cam->CameraToWorld(toFpoint(g_ptMouse));

	UpdateTimes();

	if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
	{
		cam->SetScale(cam->GetScale() - 1.0f * TimerManager::GetSingleton()->GetElapsedTime());
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown('X'))
	{
		cam->SetScale(cam->GetScale() + 1.0f * TimerManager::GetSingleton()->GetElapsedTime());
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown('C'))
	{
		dropContainer->AddDrop(Item{ (rand() % 4) + 1,1 }, FPOINT{ (float)(rand() % 1000), (float)(rand() % 1000) });
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		bool isUIClicked = false;
		POINT selTile = stage->PosToTile(worldMouse);

		if (!isUIClicked)
		{
			isUIClicked = UIObject::GetIsClicked(uiInventory->MouseDown(g_ptMouse));
		}
		
		if (!isUIClicked)
		{
			if (stage->CanBuild(RECT{ selTile.x, selTile.y, selTile.x, selTile.y }))
			{
				stage->BuildStructure(selTile, 0);
			}
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RBUTTON))
	{
		POINT selTile = stage->PosToTile(worldMouse);
		Terrain* selTerrain = stage->GetTerrain(selTile);
		if (selTerrain->GetIsLand() == false)
		{
			selTerrain->SetFloorIdx(1);
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		uiInventory->MouseUp(g_ptMouse);
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
				inventoryContainer->GetPlayerInventory()->RemoveItem(Item{ itemNum, 1 });
			}
			else
			{
				inventoryContainer->GetPlayerInventory()->AddItem(Item{ itemNum, 1 });
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


	if (KeyManager::GetSingleton()->IsStayKeyDown('Q'))
	{
		GameData::GetSingleton()->Save();
	}

	stage->Update();
	player->Update();
	CheckCollision();
	CheckCollisionPlayerAndItem();
}

void GameScene::Render(HDC hdc)
{
	SetCamera();
	PatBlt(hdc, 0, 0,
		GAMESCENESIZE_X, GAMESCENESIZE_X, WHITENESS);
	if (stage) 
	{ 
		stage->Render(hdc); 
		for (int tileY = 0; tileY < Con::TILE_Y; tileY++)
		{
			stage->RenderLine(hdc, tileY);
		}
	}
	if (player) { player->Render(hdc); }
	if (uiInventory) { uiInventory->Render(hdc); }
	if (dropContainer) { dropContainer->Render(hdc); }
}

void GameScene::InitTimes()
{
	sceneTime = 0;
	gameTime = 0;
	lastResourceRegenTime = gameTime;
}

void GameScene::UpdateTimes()
{
	sceneTime += TimerManager::GetSingleton()->GetElapsedTime();
	gameTime += TimerManager::GetSingleton()->GetElapsedTime();

	if (lastResourceRegenTime < gameTime + Con::REGEN_RESOURCE_INTERVAL)
	{
		lastResourceRegenTime += Con::REGEN_RESOURCE_INTERVAL;
		for (int i = 0; i < Con::REGEN_RESOURCE_COUNT * 10; i++)
		{
			int randResourceNum = rand() % 4;
			int randTileX = rand() % Con::TILE_X;
			int randTileY = rand() % Con::TILE_Y;
			int randResourceType;
			switch (randResourceNum)
			{
			case 0:
				randResourceType = GameData::GetSingleton()->
					FindStructureInfo("structure_tree_grass");
				break;
			case 1:
				randResourceType = GameData::GetSingleton()->
					FindStructureInfo("structure_tree_fire");
				break;
			case 2:
				randResourceType = GameData::GetSingleton()->
					FindStructureInfo("structure_tree_snow");
				break;
			case 3:
				randResourceType = GameData::GetSingleton()->
					FindStructureInfo("structure_tree_desert");
				break;
			}
			if (randResourceType != -1)
			{
				POINT randResourceSize = 
					GameData::GetSingleton()->GetStructureInfo(randResourceType)->GetTileSize();

				if (stage->CanBuild(RECT{
					randTileX, randTileY - randResourceSize.y + 1,
					randTileX + randResourceSize.x - 1, randTileY }))
				{
					stage->BuildStructure(POINT{ randTileX, randTileY }, randResourceType);
				}
			}
		}
	}
}

void GameScene::CheckCollision()
{
	if (stage && player)
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
				if (!currTerrain->GetIsFree()) 
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
}

void GameScene::CheckCollisionPlayerAndItem()
{
	if (dropContainer && player)
	{
		for (int i = 0; i < dropContainer->GetSize(); i++)
		{
			Drop* drop = dropContainer->GetDrop(i);
			if (CheckIfColliding(player, (StageObject*)drop))
			{
				dropContainer->RemoveDrop(i);
				inventoryContainer->GetPlayerInventory()->
					AddItem(drop->GetItem());
			}
		}

	}
}

void GameScene::CollisionPush(StageObject* movable, StageObject* immovable)
{
	RECT resultRect = RECT{ 0, 0, 0, 0 };
	FPOINT plPos = movable->GetPos();
	RECT plRect = movable->GetBox();
	RECT tileRect = immovable->GetBox();

	if (IntersectRect(&resultRect,
		&plRect,
		&tileRect))
	{
		POINT resultSize = POINT{
			resultRect.right - resultRect.left,
			resultRect.bottom - resultRect.top
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
}

bool GameScene::CheckIfColliding(StageObject* obj1, StageObject* obj2)
{
	RECT resultRect = RECT{ 0, 0, 0, 0 };
	RECT obj1Rect = obj1->GetBox();
	RECT obj2Rect = obj2->GetBox();

	return (IntersectRect(&resultRect, &obj1Rect, &obj2Rect));
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
