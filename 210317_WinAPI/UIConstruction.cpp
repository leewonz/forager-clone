#include "UIConstruction.h"

#include "Image.h"
#include "Stage.h"
#include "InventoryContainer.h"
#include "Camera.h"
#include "StructureInfo.h"
#include "CommonFunction.h"

HRESULT UIConstruction::Init()
{
	GameData* gameData = GameData::GetSingleton();
	int cosntructionRecipeCount = gameData->GetConstructionRecipeCount();
	buttonImg = ImageManager::GetSingleton()->FindImage("ui_button");
	bgImg = ImageManager::GetSingleton()->FindImage("ui_textBoxShort");
	selection1x1Img = ImageManager::GetSingleton()->FindImage("landSelection1x1");
	selection2x2Img = ImageManager::GetSingleton()->FindImage("landSelection2x2");
	buttonSize =  POINT{ buttonImg->GetImageInfo()->width,
		                 buttonImg->GetImageInfo()->height };

	pos.x = 1000;
	pos.y = 0;

	for (int i = 0; i < cosntructionRecipeCount; i++)
	{
		ConstructionButton tempButton = ConstructionButton();
		int currYOffset = i * ((buttonSize.y * BUTTON_SCALE) + BUTTON_GAP);

		tempButton.idx = i;
		tempButton.box = { 
			(LONG)(buttonSize.x),
			(LONG)(buttonSize.y + currYOffset),
			(LONG)(buttonSize.x + (buttonSize.x * BUTTON_SCALE)),
			(LONG)(buttonSize.y + (buttonSize.y * BUTTON_SCALE) + currYOffset)
		};

		constructionButtons.push_back(tempButton);

	}

	return S_OK;
}

pair<UI_MESSAGE, int> UIConstruction::Back()
{
	return { UI_MESSAGE::NONE, 0 };
}

bool UIConstruction::IsMaterialEnough(Item* items, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (items[i].idx > 0 &&
			container->GetItemCount(items[i].idx) < items[i].count)
		{
			return false;
		}
	}
	return true;
}

void UIConstruction::RemoveMaterial(Item* items, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (items[i].idx > 0)
		{
			container->RemoveItem(items[i]);
		}
	}
}

pair<UI_MESSAGE, int> UIConstruction::MouseDown(POINT mousePos)
{
	if(isActive)
	{
		Camera* cam = Camera::GetSingleton();
		GameData* gameData = GameData::GetSingleton();
		FPOINT worldMousePos = cam->CameraToWorld(toFpoint(mousePos));

		for (int i = 0; i < constructionButtons.size(); i++)
		{
			RECT buttonBox = RECT{ (LONG)(pos.x + constructionButtons[i].box.left),
								   (LONG)(pos.y + constructionButtons[i].box.top),
								   (LONG)(pos.x + constructionButtons[i].box.right),
								   (LONG)(pos.y + constructionButtons[i].box.bottom) };
			if (PointInRect(mousePos, buttonBox))
			{
				selectedConstuction = i;
				return { UI_MESSAGE::OK, 0 };
			}
		}

		if (selectedConstuction != -1 && stage)
		{
			ConstructionRecipe* recipe = gameData->GetConstructionRecipe(selectedConstuction);
			if (recipe->constructionCategory == ConstructionCategory::STRUCTURE)
			{
				int structureIdx = recipe->constructionIdx;
				StructureInfo* info = gameData->GetStructureInfo(structureIdx);
				POINT selectedTilePoint =
					stage->PosToTile(POINT{
						(int)(worldMousePos.x - ((info->GetTileSize().x - 1) * Con::TILESIZE / 2)),
						(int)(worldMousePos.y + ((info->GetTileSize().y - 1) * Con::TILESIZE / 2)) });
				RECT selectedTileRect = RECT{
					selectedTilePoint.x, selectedTilePoint.y - info->GetTileSize().y + 1,
					selectedTilePoint.x + info->GetTileSize().x - 1, selectedTilePoint.y };
					//stage->CenterPosToTile(worldMousePos, info->GetTileSize());
				if (stage->CanBuild(selectedTileRect) &&
					IsMaterialEnough(recipe->materials, Con::CONSTRUCTION_MATERIAL_MAX))
				{
					stage->BuildStructure(POINT{ selectedTilePoint.x, selectedTilePoint.y }, structureIdx);
					RemoveMaterial(recipe->materials, Con::CONSTRUCTION_MATERIAL_MAX);
					return { UI_MESSAGE::OK, 0 };
				}
			}
			else if (recipe->constructionCategory == ConstructionCategory::FLOOR)
			{
				int floorIdx = recipe->constructionIdx;
				FloorInfo* info = gameData->GetFloorInfo(floorIdx);
				POINT selectedTile =
					stage->PosToTile(worldMousePos);
				Terrain* selTerrain = stage->GetTerrain(selectedTile);
				if (selTerrain &&
					selTerrain->GetIsLand() == false &&
					selTerrain->GetFloorIdx() == 0 &&
					IsMaterialEnough(recipe->materials, Con::CONSTRUCTION_MATERIAL_MAX)
					)
				{
					selTerrain->SetFloorIdx(floorIdx);
					RemoveMaterial(recipe->materials, Con::CONSTRUCTION_MATERIAL_MAX);
					return { UI_MESSAGE::OK, 0 };
				}
			}
		}
	}

	return { UI_MESSAGE::OK, 0 };
}

pair<UI_MESSAGE, int> UIConstruction::MouseUp(POINT mousePos)
{
	return { UI_MESSAGE::NONE, 0 };
}

void UIConstruction::OnActivate()
{
}

void UIConstruction::OnDeactivate()
{
}

void UIConstruction::Render(HDC hdc)
{
	if (isActive)
	{
		GameData* gameData = GameData::GetSingleton();
		TimerManager* timerM = TimerManager::GetSingleton();
		FPOINT worldSpaceMouse = Camera::GetSingleton()->CameraToWorld(toFpoint(g_ptMouse));
		int cosntructionRecipeCount = gameData->GetConstructionRecipeCount();

		for (int i = 0; i < constructionButtons.size(); i++)
		{
			ConstructionRecipe* recipe = gameData->GetConstructionRecipe(i);
			Image* constructionIconimg = recipe->iconImg;
			POINT constructionIconPos = POINT{ constructionButtons[i].box.left + BUTTON_ICON_OFFSET.x,
											   constructionButtons[i].box.top + BUTTON_ICON_OFFSET.y };
			buttonImg->Render(
				hdc,
				pos.x + constructionButtons[i].box.left,
				pos.y + constructionButtons[i].box.top,
				2.0f, false);
			constructionIconimg->Render(
				hdc,
				pos.x + constructionButtons[i].box.left + BUTTON_ICON_OFFSET.x,
				pos.y + constructionButtons[i].box.top + BUTTON_ICON_OFFSET.y - constructionIconimg->GetFrameHeight(),
				1.0f, false);
			wsprintf(szText, "%s", gameData->GetStructureInfo(recipe->constructionIdx)->GetName().c_str());
			TextOut(hdc,
				pos.x + constructionButtons[i].box.left + BUTTON_ICON_OFFSET.x + 32,
				pos.y + constructionButtons[i].box.top + BUTTON_ICON_OFFSET.y - 20,
				szText, strlen(szText));
			if (i == selectedConstuction && container)
			{
				POINT textBoxPoint = POINT{
					GAMESCENESIZE_X - bgImg->GetImageInfo()->frameWidth - 12,
					GAMESCENESIZE_Y - bgImg->GetImageInfo()->frameHeight - 12 };
				bgImg->Render(hdc,
					textBoxPoint.x,
					textBoxPoint.y,
					1.0f, false);
				constructionIconimg->Render(
					hdc,
					textBoxPoint.x + 12,
					textBoxPoint.y + 40 - constructionIconimg->GetFrameHeight(),
					1.0f, false);
				if (recipe->constructionCategory == ConstructionCategory::STRUCTURE)
				{
					wsprintf(szText, "%s", gameData->GetStructureInfo(recipe->constructionIdx)->GetName().c_str());
				}
				else if (recipe->constructionCategory == ConstructionCategory::FLOOR)
				{
					wsprintf(szText, "%s", gameData->GetFloorInfo(recipe->constructionIdx)->name.c_str());
				}
				TextOut(hdc,
					textBoxPoint.x + 64,
					textBoxPoint.y + 16,
					szText, strlen(szText));
				for (int matIdx = 0; matIdx < Con::CONSTRUCTION_MATERIAL_MAX; matIdx++)
				{
					Item item = recipe->materials[matIdx];
					int inventoryItemCount = container->GetItemCount(item.idx);
					if (item.idx >= 0)
					{
						ItemInfo* info = gameData->GetItemInfo(item.idx);
						info->img->Render(
							hdc,
							textBoxPoint.x + 12,
							textBoxPoint.y + 64 + (matIdx * 32),
							1.0f, false);
						wsprintf(szText, "%s : %d / %d", info->name.c_str(), inventoryItemCount, item.count);
						TextOut(hdc,
							textBoxPoint.x + 48,
							textBoxPoint.y + 72 + (matIdx * 32),
							szText, strlen(szText));
					}
				}
				if (recipe->constructionCategory == ConstructionCategory::STRUCTURE)
				{
					POINT tileSize = gameData->GetStructureInfo(recipe->constructionIdx)->GetTileSize();
					if (tileSize.x == 1)
					{
						POINT mouseGrid = stage->PosToTile(worldSpaceMouse);
						mouseGrid.x = (mouseGrid.x * Con::TILESIZE) - 8;
						mouseGrid.y = (mouseGrid.y * Con::TILESIZE) - 8;
						selection1x1Img->StageRender(hdc,
							mouseGrid.x, mouseGrid.y,
							(int)(timerM->GetProgramTime() * 10.0f) % 10, 0, false, 1.0f);
					}
					if (tileSize.x == 2)
					{
						POINT mouseGrid = stage->PosToTile(
							FPOINT{ (float)(worldSpaceMouse.x - (Con::TILESIZE / 2)),
							(float)(worldSpaceMouse.y - (Con::TILESIZE / 2)) });
						mouseGrid.x = (mouseGrid.x * Con::TILESIZE) - 4;
						mouseGrid.y = (mouseGrid.y * Con::TILESIZE) - 4;
						selection2x2Img->StageRender(hdc,
							mouseGrid.x, mouseGrid.y,
							(int)(timerM->GetProgramTime() * 10.0f) % 10, 0, false, 1.0f);
					}
				}
				else if (recipe->constructionCategory == ConstructionCategory::FLOOR)
				{
					POINT mouseGrid = stage->PosToTile(worldSpaceMouse);
					mouseGrid.x = (mouseGrid.x * Con::TILESIZE) - 8;
					mouseGrid.y = (mouseGrid.y * Con::TILESIZE) - 8;
					selection1x1Img->StageRender(hdc,
						mouseGrid.x, mouseGrid.y,
						(int)(timerM->GetProgramTime() * 10.0f) % 10, 0, false, 1.0f);
				}
			}
		}
	}
}
