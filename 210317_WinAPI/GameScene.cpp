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
#include "UIConstruction.h"
#include "UIContainer.h"
#include "UICrafting.h"
#include "DropContainer.h"
#include "Drop.h"
#include "GameData.h"
#include "StructureInfo.h"
#include "Structure.h"
#include "config.h"
#include "CommonFunction.h"

HRESULT GameScene::Init()
{
	SetClientRect(g_hWnd, GAMESCENESIZE_X, GAMESCENESIZE_Y);

	InitTimes();

	Camera* cam = Camera::GetSingleton();
	cam->SetScreenSize(POINT{ GAMESCENESIZE_X , GAMESCENESIZE_Y });
	cam->SetScale(3.0f);

	stage = new Stage();
	stage->Init(POINT{ Con::TILESIZE, Con::TILESIZE });
	stage->Load();

	player = new Player();
	player->Init();
	player->SetPos(FPOINT{ Con::TILE_X * Con::TILESIZE / 2, Con::TILE_Y * Con::TILESIZE / 2 });

	inventoryContainer = new InventoryContainer();
	inventoryContainer->Init();

	dropContainer = new DropContainer();
	dropContainer->Init(this);

	uiInventory = new UIInventory();
	uiInventory->Init(POINT{ Con::INVEN_PLAYER_X, Con::INVEN_PLAYER_Y });
	uiInventory->SetInventory(inventoryContainer->GetPlayerInventory());

	uiConstruction = new UIConstruction();
	uiConstruction->Init();
	uiConstruction->SetStage(stage);
	uiConstruction->SetInventoryContainer(inventoryContainer);

	uiContainer = new UIContainer();
	uiContainer->Init();
	uiContainer->AddChild(uiInventory);
	uiContainer->AddChild(uiConstruction);
	uiContainer->SetActive(false);

	uiCrafting = new UICrafting();
	uiCrafting->Init();
	uiCrafting->SetActive(false);
	uiCrafting->SetInventoryContainer(inventoryContainer);
	uiCrafting->SetDropContainer(dropContainer);

	camPos = player->GetPos();

	keyboardEImg = ImageManager::GetSingleton()->FindImage("keyboardE");

	//for(int i = 0; i < 5000; i++)
	//{
	//	dropContainer->AddDrop(
	//		Item{ (rand() % 4) + 1,1 },
	//		FPOINT{ (float)(rand() % (Con::TILE_X * Con::TILESIZE)),
	//				(float)(rand() % (Con::TILE_Y * Con::TILESIZE)) });
	//}

	return S_OK;
}

void GameScene::Release()
{
	SAFE_RELEASE(stage);
	SAFE_RELEASE(player);
	SAFE_RELEASE(inventoryContainer);
	SAFE_RELEASE(dropContainer);
	//SAFE_RELEASE(uiInventory);
	//SAFE_RELEASE(uiConstruction);
	SAFE_RELEASE(uiContainer);
	SAFE_RELEASE(uiCrafting);
}

void GameScene::Update()
{
	Camera* cam = Camera::GetSingleton();
	GameData* gameData = GameData::GetSingleton();
	FPOINT worldMouse = cam->CameraToWorld(toFpoint(g_ptMouse));

	UpdateTimes();

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_OEM_MINUS))
	{
		cam->SetScale(cam->GetScale() - 2.0f * TimerManager::GetSingleton()->GetElapsedTime());
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_OEM_PLUS))
	{
		cam->SetScale(cam->GetScale() + 2.0f * TimerManager::GetSingleton()->GetElapsedTime());
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown('C'))
	{
		for (int i = 0; i < 5; i++)
		{
			dropContainer->AddDrop(
				Item{ (rand() % GameData::GetSingleton()->GetItemInfoCount() - 1) + 1, 20 },
				FPOINT{ (float)(((rand() % 20) - 10.0f) * Con::TILESIZE) + player->GetPos().x,
						(float)(((rand() % 20) - 10.0f) * Con::TILESIZE) + player->GetPos().y });
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		//bool isUIClicked = false;
		//POINT selTile = stage->PosToTile(worldMouse);
		//Terrain* selTerrain = stage->GetTerrain(selTile);

		if (UIObject::GetIsClicked(uiContainer->MouseDown(g_ptMouse)) == false &&
			UIObject::GetIsClicked(uiCrafting->MouseDown(g_ptMouse)) == false)
		{
			POINT selTile = stage->PosToTile(worldMouse);
			//stage->DestroyStructure(stage->GetTerrain(selTile)->GetStructure());
			Structure* structure = stage->GetStructureAtPoint(worldMouse);
			if (structure)
			{
				SpawnDrop(structure);
				stage->DestroyStructure(structure);
			}
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RBUTTON))
	{

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

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		if (uiCrafting && uiCrafting->GetActive())
		{
			uiCrafting->Back();
		}
		else if (uiContainer)
		{
			if (uiContainer->GetActive())
			{
				uiContainer->Back();
			}
			else
			{
				uiContainer->SetActive(true);
			}
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))
	{
		Structure* structure = stage->GetStructureAtPoint(worldMouse);
		if (structure && uiCrafting && uiContainer->GetActive() == false)
		{
			StructureInfo* info = gameData->GetStructureInfo(structure->GetStructureType());
			if (info->GetCodename() == "forge" ||
				info->GetCodename() == "furnace")
			{
				uiCrafting->SetStructure(structure);
				uiCrafting->SetActive(false);
				uiCrafting->SetActive(true);
			}
		}
	}
	
	if (KeyManager::GetSingleton()->IsStayKeyDown('Q'))
	{
		GameData::GetSingleton()->Save();
	}

	if (stage) { stage->Update(); }
	if (player) { player->Update(); }
	if (dropContainer) { dropContainer->Update(); }
	CheckCollision();
	CheckCollisionPlayerAndItem();
	SetCamera();
	UpdateCrafting();
}

void GameScene::Render(HDC hdc)
{
	GameData* gameData = GameData::GetSingleton();
	Camera* cam = Camera::GetSingleton();
	FPOINT worldMouse = cam->CameraToWorld(toFpoint(g_ptMouse)); 
	Structure* structure = stage->GetStructureAtPoint(worldMouse);

	PatBlt(hdc, 0, 0,
		GAMESCENESIZE_X, GAMESCENESIZE_X, WHITENESS);
	SetBkMode(hdc, TRANSPARENT);

	if (stage && dropContainer) 
	{ 
		int playerY = -1;

		map<float, Drop*>::iterator currDropIter;
		map<float, Drop*>::iterator currDropIterEnd;

		stage->Render(hdc); 

		currDropIter = dropContainer->getMapBegin();
		currDropIterEnd = dropContainer->getMapEnd();

		if (player)
		{
			playerY = (player->GetBox().bottom - (Con::TILESIZE / 2)) / Con::TILESIZE;
		}

		for (int tileY = 0; tileY < Con::TILE_Y; tileY++)
		{
			stage->RenderLine(hdc, tileY);

			if (player && playerY == tileY)
			{
				player->Render(hdc);
			}

			while (currDropIter != currDropIterEnd &&
				(int)currDropIter->first / Con::TILESIZE <= tileY)
			{
				currDropIter->second->Render(hdc);
				++currDropIter;
			}
		}
	}

	if (structure && uiCrafting && uiContainer->GetActive() == false)
	{
		StructureInfo* info = gameData->GetStructureInfo(structure->GetStructureType());
		if (info->GetCodename() == "forge" ||
			info->GetCodename() == "furnace")
		{
			keyboardEImg->StageRender(hdc, structure->GetPos().x, structure->GetPos().y, 0, 0,true, 0.2f);
		}
	}

	if (uiContainer) { uiContainer->Render(hdc); }
	if (uiCrafting) { uiCrafting->Render(hdc); }
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

	if (lastResourceRegenTime + Con::REGEN_RESOURCE_INTERVAL < gameTime)
	{
		lastResourceRegenTime += Con::REGEN_RESOURCE_INTERVAL;
		for (int i = 0; i < Con::REGEN_RESOURCE_COUNT; i++)
		{
			int randResourceNum = rand() % 5;
			int randTileX = rand() % Con::TILE_X;
			int randTileY = rand() % Con::TILE_Y;
			int randResourceType = -1;
			string structureCodename = "";
			Terrain* terrain = stage->GetTerrain(POINT{ randTileX , randTileY });
			TerrainType terrainType = terrain->GetTerrainType();
			switch (randResourceNum)
			{
			case 0:
				switch (terrainType)
				{
				case TerrainType::GRASS:
					structureCodename = "tree_grass";
					break;
				case TerrainType::DESERT:
					structureCodename = "tree_desert";
					break;
				case TerrainType::WINTER:
					structureCodename = "tree_snow";
					break;
				case TerrainType::GRAVEYARD:
					structureCodename = "tree_fire";
					break;
				case TerrainType::FIRE:
					structureCodename = "tree_fire";
					break;
				}
				break;
			case 1:
				structureCodename = "stone";
				break;
			case 2:
				structureCodename = "coal";
				break;
			case 3:
				structureCodename = "iron";
				break;
			case 4:
				structureCodename = "gold";
				break;
			}
			randResourceType = GameData::GetSingleton()->
				FindStructureInfo(structureCodename);
			if (randResourceType != -1)
			{
				POINT randResourceSize = 
					GameData::GetSingleton()->GetStructureInfo(randResourceType)->GetTileSize();

				if (stage->CanBuild(RECT{
					randTileX, randTileY - randResourceSize.y + 1,
					randTileX + randResourceSize.x - 1, randTileY }) &&
					terrain->GetIsLand()
					)
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
				if (!currTerrain->GetIsPassable()) 
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
			if (CheckIfColliding(player, (StageObject*)drop) &&
				drop->IsAnimationEnded())
			{
				inventoryContainer->AddDropItem(drop->GetItem());

				dropContainer->RemoveDrop(i);
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

void GameScene::SpawnDrop(Structure* structure)
{
	vector<Item> drops = structure->GetDrops();
	for (int i = 0; i < drops.size(); i++)
	{
		dropContainer->AddDrop(drops[i], structure->GetPos());
	}
}

float GameScene::GetGameTime()
{
	return gameTime;
}

float GameScene::GetSceneTime()
{
	return sceneTime;
}

void GameScene::UpdateCrafting()
{
	if (stage)
	{
		int structureCount = stage->GetStructureCount();
		for (int i = 0; i < structureCount; i++)
		{
			Structure* structure = stage->GetStructure(i);
			if (structure)
			{
				vector<Item> outputs = structure->GetCraftingOutputItems();

				structure->Update();

				// 크래프팅 결과물 받아서 드롭아이템 생성
				for (int i = 0; i < outputs.size(); i++)
				{
					RECT structureRect = structure->GetTileFullBox();
					dropContainer->AddDrop(
						outputs[i], 
						FPOINT{ ((float)(structureRect.left + structureRect.right) * 0.5f), (float)(structureRect.bottom) });
				}
				structure->ResetCraftingOutputItems();

				// 무한 크래프팅 (인벤에서 아이템 강탈 후 제작)
				if (structure->GetIsCraftingInfinite() && structure->GetCraftingInputCount() == 0)
				{
					bool canCraftInf = true;
					vector<Item> items = structure->GetCraftingRequiredItems();

					for (int i = 0; i < items.size(); i++)
					{
						if (inventoryContainer->GetItemCount(items[i].idx) < items[i].count)
						{
							canCraftInf = false;
						}
					}

					if(canCraftInf)
					{
						for (int i = 0; i < items.size(); i++)
						{
							inventoryContainer->RemoveItem(items[i]);
						}

						structure->ResumeCraftingInfinite();
					}
				}
			}
		}
	}
}
