#include "UICrafting.h"
#include "GameData.h"
#include "Image.h"
#include "Structure.h"
#include "inventoryContainer.h"
#include "CommonFunction.h"

HRESULT UICrafting::Init()
{
	GameData* gameData = GameData::GetSingleton();
	buttonImg = ImageManager::GetSingleton()->FindImage("ui_button");
	bgImg = ImageManager::GetSingleton()->FindImage("ui_textBox");
	arrowImg = ImageManager::GetSingleton()->FindImage("ui_arrowSmall");
	buttonSize = POINT{ buttonImg->GetImageInfo()->width,
						 buttonImg->GetImageInfo()->height };

	pos.x = 500;
	pos.y = 200;

	for (int i = 0; i < BUTTON_MAX_COUNT; i++)
	{
		CraftingButton tempButton = CraftingButton();
		int currYOffset = i * ((buttonSize.y * BUTTON_SCALE) + BUTTON_GAP);

		tempButton.idx = i;
		tempButton.box = {
			(LONG)(0),
			(LONG)(0 + currYOffset),
			(LONG)(0 + (buttonSize.x * BUTTON_SCALE)),
			(LONG)(0 + (buttonSize.y * BUTTON_SCALE) + currYOffset)
		};

		craftingButtons.push_back(tempButton);

	}

	resultBGPoint = POINT{
		(LONG)(craftingButtons[0].box.right + 16),
		(LONG)(0),
	};
	craftButtonPoint = POINT{
		(LONG)(resultBGPoint.x + 20),
		(LONG)(resultBGPoint.y + 200)};

	craftInfiniteButtonPoint = POINT{
		(LONG)(craftButtonPoint.x),
		(LONG)(craftButtonPoint.y + BUTTON_GAP + (buttonSize.y * BUTTON_SCALE ))};

	return S_OK;
}

void UICrafting::Render(HDC hdc)
{
	if (isActive && structure)
	{
		GameData* gameData = GameData::GetSingleton();
		vector<CraftingRecipe*> recipes = structure->GetRecipeList();

		for (int i = 0; i < (min(recipes.size(), BUTTON_MAX_COUNT)); i++)
		{
			CraftingRecipe* currRecipe = recipes[i];
			ItemInfo* resultItemInfo = gameData->GetItemInfo(currRecipe->resultItemIdx);
			Image* resultItemImg = resultItemInfo->img;
			POINT constructionIconPos = POINT{ craftingButtons[i].box.left + BUTTON_ICON_OFFSET.x,
											   craftingButtons[i].box.top + BUTTON_ICON_OFFSET.y };
			buttonImg->Render(
				hdc,
				pos.x + craftingButtons[i].box.left,
				pos.y + craftingButtons[i].box.top,
				BUTTON_SCALE, false);
			resultItemImg->Render(
				hdc,
				pos.x + constructionIconPos.x,
				pos.y + constructionIconPos.y,
				1.0f, false);
			wsprintf(szText, "%s", resultItemInfo->name.c_str());
			TextOut(hdc,
				pos.x + constructionIconPos.x + 32,
				pos.y + constructionIconPos.y + 0,
				szText, strlen(szText));

			if (i == selectedRecipe)
			{
				POINT resultIconPoint = POINT{
					resultBGPoint.x + 32,
					resultBGPoint.y + 32
				};
				bgImg->Render(
					hdc,
					pos.x + resultBGPoint.x,
					pos.y + resultBGPoint.y,
					1.0f, false);
				resultItemImg->Render(
					hdc,
					pos.x + resultIconPoint.x,
					pos.y + resultIconPoint.y,
					2.0f, false);
				wsprintf(szText, "%s", resultItemInfo->name.c_str());
				TextOut(hdc,
					pos.x + resultIconPoint.x + 64,
					pos.y + resultIconPoint.y + 32,
					szText, strlen(szText));

				for (int matIdx = 0; matIdx < Con::CRAFTING_MATERIAL_MAX; matIdx++)
				{
					Item item = currRecipe->materials[matIdx];
					int inventoryItemCount = inventoryContainer->GetItemCount(item.idx);
					POINT recipeIconPoint = POINT{
						(LONG)(resultBGPoint.x + 32),
						(LONG)(resultBGPoint.y + (matIdx * 32) + 128),
					};
					if (item.idx > 0)
					{
						ItemInfo* info = gameData->GetItemInfo(item.idx);
						info->img->Render(
							hdc,
							pos.x + recipeIconPoint.x,
							pos.y + recipeIconPoint.y,
							1.0f, false);
						wsprintf(szText, "%s : %d / %d", info->name.c_str(), inventoryItemCount, item.count);
						TextOut(hdc,
							pos.x + recipeIconPoint.x + 32,
							pos.y + recipeIconPoint.y,
							szText, strlen(szText));
					}
				}

				buttonImg->Render(
					hdc,
					pos.x + craftButtonPoint.x,
					pos.y + craftButtonPoint.y,
					BUTTON_SCALE, false);

				buttonImg->Render(
					hdc,
					pos.x + craftInfiniteButtonPoint.x,
					pos.y + craftInfiniteButtonPoint.y,
					BUTTON_SCALE, false);
			}
		}
	}
}

pair<UI_MESSAGE, int> UICrafting::MouseDown(POINT mousePos)
{
	if (isActive && structure)
	{
		GameData* gameData = GameData::GetSingleton();
		vector<CraftingRecipe*> recipes = structure->GetRecipeList();
		RECT craftingButtonRect = RECT{
			(LONG)(pos.x + craftButtonPoint.x),
			(LONG)(pos.y + craftButtonPoint.y),
			(LONG)(pos.x + craftButtonPoint.x + (buttonSize.x * BUTTON_SCALE)),
			(LONG)(pos.y + craftButtonPoint.y + (buttonSize.y * BUTTON_SCALE)) };
		RECT craftingInfButtonRect = RECT{
			(LONG)(pos.x + craftInfiniteButtonPoint.x),
			(LONG)(pos.y + craftInfiniteButtonPoint.y),
			(LONG)(pos.x + craftInfiniteButtonPoint.x + (buttonSize.x * BUTTON_SCALE)),
			(LONG)(pos.y + craftInfiniteButtonPoint.y + (buttonSize.y * BUTTON_SCALE)) };

		for (int i = 0; i < (min(recipes.size(), BUTTON_MAX_COUNT)); i++)
		{
			RECT CurrButtonRect = RECT{ (LONG)(pos.x + craftingButtons[i].box.left),
										(LONG)(pos.y + craftingButtons[i].box.top),
										(LONG)(pos.x + craftingButtons[i].box.right),
										(LONG)(pos.y + craftingButtons[i].box.bottom) };

			if (PointInRect(mousePos, CurrButtonRect))
			{
				selectedRecipe = i;
				return { UI_MESSAGE::OK, 0 };
			}
		}

		if (PointInRect(mousePos, craftingButtonRect))
		{
			vector<Item> items= structure->GetCraftingMaterials(selectedRecipe, 1);

			for (int i = 0; i < items.size(); i++)
			{
				if (inventoryContainer->GetItemCount(items[i].idx) < items[i].count)
				{
					return { UI_MESSAGE::OK, 0 };
				}
			}

			structure->StopCrafting();

			for (int i = 0; i < items.size(); i++)
			{
				inventoryContainer->RemoveItem(items[i]);
			}

			structure->StartCrafting(selectedRecipe, 1);
		}

		if (PointInRect(mousePos, craftingInfButtonRect))
		{
			structure->StartCraftingInfinite(selectedRecipe);
		}
	}
	return { UI_MESSAGE::NONE, 0 };
}

pair<UI_MESSAGE, int> UICrafting::MouseUp(POINT mousePos)
{
	return { UI_MESSAGE::NONE, 0 };
}

pair<UI_MESSAGE, int> UICrafting::Back()
{
	this->SetActive(false);
	return {UI_MESSAGE::BACK, 0};
}

void UICrafting::OnActivate()
{
	selectedRecipe = -1;
}

void UICrafting::OnDeactivate()
{
}
