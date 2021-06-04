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
	buttonSmallImg = ImageManager::GetSingleton()->FindImage("ui_buttonSmall");
	bgImg = ImageManager::GetSingleton()->FindImage("ui_textBox");
	arrowImg = ImageManager::GetSingleton()->FindImage("ui_arrowSmall");
	buttonSize = POINT{ buttonImg->GetImageInfo()->width,
						 buttonImg->GetImageInfo()->height };
	buttonSmallSize = POINT{ buttonSmallImg->GetImageInfo()->width,
					 buttonSmallImg->GetImageInfo()->height };

	pos.x = 450;
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
		(LONG)(resultBGPoint.y + 220)};

	craftInfiniteButtonPoint = POINT{
		(LONG)(craftButtonPoint.x),
		(LONG)(craftButtonPoint.y + BUTTON_GAP + (buttonSmallSize.y * BUTTON_SCALE ))};

	craftStopButtonPoint = POINT{
		(LONG)(craftInfiniteButtonPoint.x),
		(LONG)(craftInfiniteButtonPoint.y + BUTTON_GAP + (buttonSmallSize.y * BUTTON_SCALE ))};

	arrowLRect = RECT{
		(LONG)(craftButtonPoint.x),
		(LONG)(craftButtonPoint.y - (arrowImg->GetImageInfo()->frameHeight * BUTTON_SCALE)),
		(LONG)(craftButtonPoint.x + (arrowImg->GetImageInfo()->frameWidth * BUTTON_SCALE)),
		(LONG)(craftButtonPoint.y)
	};

	arrowRRect = RECT{
		(LONG)(craftButtonPoint.x - (arrowImg->GetImageInfo()->frameWidth * BUTTON_SCALE) + (buttonImg->GetImageInfo()->frameWidth * BUTTON_SCALE)),
		(LONG)(craftButtonPoint.y - (arrowImg->GetImageInfo()->frameHeight * BUTTON_SCALE)),
		(LONG)(craftButtonPoint.x + (buttonImg->GetImageInfo()->frameWidth * BUTTON_SCALE)),
		(LONG)(craftButtonPoint.y)
	};

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
				pos.y + constructionIconPos.y + 8,
				szText, strlen(szText));

			if (i == selectedRecipe)
			{
				POINT resultIconPoint = POINT{
					resultBGPoint.x + 32,
					resultBGPoint.y + 16
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
						(LONG)(resultBGPoint.y + (matIdx * 24) + 80),
					};
					if (item.idx > 0)
					{
						ItemInfo* info = gameData->GetItemInfo(item.idx);
						info->img->Render(
							hdc,
							pos.x + recipeIconPoint.x,
							pos.y + recipeIconPoint.y,
							1.0f, false);
						wsprintf(szText, "%s : %d / %d", info->name.c_str(), inventoryItemCount, item.count * craftAmount);
						TextOut(hdc,
							pos.x + recipeIconPoint.x + 32,
							pos.y + recipeIconPoint.y + 8,
							szText, strlen(szText));
					}
				}

				buttonSmallImg->Render(
					hdc,
					pos.x + craftButtonPoint.x,
					pos.y + craftButtonPoint.y,
					BUTTON_SCALE, false);
				wsprintf(szText, "%d%s", craftAmount, Con::TEXT_CRAFTING_START_BUTTON.c_str());
				TextOut(hdc,
					pos.x + craftButtonPoint.x + 24,
					pos.y + craftButtonPoint.y + 12,
					szText, strlen(szText));

				buttonSmallImg->Render(
					hdc,
					pos.x + craftInfiniteButtonPoint.x,
					pos.y + craftInfiniteButtonPoint.y,
					BUTTON_SCALE, false);
				wsprintf(szText, "%s", Con::TEXT_CRAFTING_INFINITE_BUTTON.c_str());
				TextOut(hdc,
					pos.x + craftInfiniteButtonPoint.x + 24,
					pos.y + craftInfiniteButtonPoint.y + 12,
					szText, strlen(szText));

				buttonSmallImg->Render(
					hdc,
					pos.x + craftStopButtonPoint.x,
					pos.y + craftStopButtonPoint.y,
					BUTTON_SCALE, false);
				wsprintf(szText, "%s", Con::TEXT_CRAFTING_STOP_BUTTON.c_str());
				TextOut(hdc,
					pos.x + craftStopButtonPoint.x + 24,
					pos.y + craftStopButtonPoint.y + 12,
					szText, strlen(szText));

				arrowImg->FrameRender(
					hdc,
					pos.x + arrowLRect.left,
					pos.y + arrowLRect.top,
					0, 0, false, BUTTON_SCALE);

				arrowImg->FrameRender(
					hdc,
					pos.x + arrowRRect.left,
					pos.y + arrowRRect.top,
					1, 0, false, BUTTON_SCALE);

				wsprintf(szText, "%s%d", Con::TEXT_CRAFTING_AMOUNT.c_str(), craftAmount);
				TextOut(hdc,
					pos.x + ((arrowLRect.left + arrowRRect.left - 20) / 2),
					pos.y + arrowLRect.top,
					szText, strlen(szText));
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
			(LONG)(pos.x + craftButtonPoint.x + (buttonSmallSize.x * BUTTON_SCALE)),
			(LONG)(pos.y + craftButtonPoint.y + (buttonSmallSize.y * BUTTON_SCALE)) };
		RECT craftingInfButtonRect = RECT{
			(LONG)(pos.x + craftInfiniteButtonPoint.x),
			(LONG)(pos.y + craftInfiniteButtonPoint.y),
			(LONG)(pos.x + craftInfiniteButtonPoint.x + (buttonSmallSize.x * BUTTON_SCALE)),
			(LONG)(pos.y + craftInfiniteButtonPoint.y + (buttonSmallSize.y * BUTTON_SCALE)) };
		RECT craftingStopButtonRect = RECT{
			(LONG)(pos.x + craftStopButtonPoint.x),
			(LONG)(pos.y + craftStopButtonPoint.y),
			(LONG)(pos.x + craftStopButtonPoint.x + (buttonSmallSize.x * BUTTON_SCALE)),
			(LONG)(pos.y + craftStopButtonPoint.y + (buttonSmallSize.y * BUTTON_SCALE)) };
		RECT arrowLButtonRect = RECT{
			(LONG)(pos.x + arrowLRect.left),
			(LONG)(pos.y + arrowLRect.top),
			(LONG)(pos.x + arrowLRect.right),
			(LONG)(pos.y + arrowLRect.bottom)};
		RECT arrowRButtonRect = RECT{
			(LONG)(pos.x + arrowRRect.left),
			(LONG)(pos.y + arrowRRect.top),
			(LONG)(pos.x + arrowRRect.right),
			(LONG)(pos.y + arrowRRect.bottom) };

		for (int i = 0; i < (min(recipes.size(), BUTTON_MAX_COUNT)); i++)
		{
			RECT CurrButtonRect = RECT{ (LONG)(pos.x + craftingButtons[i].box.left),
										(LONG)(pos.y + craftingButtons[i].box.top),
										(LONG)(pos.x + craftingButtons[i].box.right),
										(LONG)(pos.y + craftingButtons[i].box.bottom) };

			if (PointInRect(mousePos, CurrButtonRect))
			{
				selectedRecipe = i;
				craftAmount = 1;
				return { UI_MESSAGE::OK, 0 };
			}
		}

		if (PointInRect(mousePos, craftingButtonRect))
		{
			vector<Item> items= structure->GetCraftingMaterials(selectedRecipe, craftAmount);

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

			structure->StartCrafting(selectedRecipe, craftAmount);
		}

		if (PointInRect(mousePos, craftingInfButtonRect))
		{
			structure->StartCraftingInfinite(selectedRecipe);
			return { UI_MESSAGE::OK, 0 };
		}
		if (PointInRect(mousePos, craftingStopButtonRect))
		{
			structure->StopCrafting(); 
			return { UI_MESSAGE::OK, 0 };
		}
		if (PointInRect(mousePos, arrowLButtonRect))
		{
			craftAmount = max(1, craftAmount - 1);
			return { UI_MESSAGE::OK, 0 };
		}
		if (PointInRect(mousePos, arrowRButtonRect))
		{
			vector<Item> items = structure->GetCraftingMaterials(selectedRecipe, craftAmount + 1);

			for (int i = 0; i < items.size(); i++)
			{
				if (inventoryContainer->GetItemCount(items[i].idx) < items[i].count)
				{
					return { UI_MESSAGE::OK, 0 };
				}
			}
			craftAmount += 1;
			return { UI_MESSAGE::OK, 0 };
		}
		return { UI_MESSAGE::BLOCKED, 0 };
	}
	else
	{
		return { UI_MESSAGE::NONE, 0 };
	}
}

pair<UI_MESSAGE, int> UICrafting::MouseUp(POINT mousePos)
{
	if (isActive)
	{
		return { UI_MESSAGE::BLOCKED, 0 };
	}
	else
	{
		return { UI_MESSAGE::NONE, 0 };
	}
}

pair<UI_MESSAGE, int> UICrafting::Back()
{
	this->SetActive(false);
	return {UI_MESSAGE::BACK, 0};
}

void UICrafting::OnActivate()
{
	if (structure && structure->GetRecipeList().size() >= 0)
	{
		selectedRecipe = 0;
	}
	else
	{
		selectedRecipe = -1;
	}

	craftAmount = 1;
}

void UICrafting::OnDeactivate()
{
}
