#include "Structure.h"
#include "StructureInfo.h"
#include "GameData.h"
#include "Stage.h"
#include "Image.h"
#include "InventoryContainer.h"

HRESULT Structure::Init(Stage* parentStage)
{
	tileFullBox = GetBox();
	SetStage(parentStage);
	craftingIdx = -1;
	return S_OK;
}

void Structure::Release()
{
	parentStage = nullptr;
}

void Structure::Update()
{
	CraftingUpdate();
}

void Structure::Render(HDC hdc)
{
	StructureInfo* info = GameData::GetSingleton()->GetStructureInfo(type);
	
	RECT box = GetBox();
	POINT imgOffset = info->GetImgOffset();

	info->GetImg()->
		StageRender(hdc, tileFullBox.left + imgOffset.x, tileFullBox.top + imgOffset.y, imageRandomFrame, 0, false, 1);
	//Image::StageRectangle(hdc, tileFullBox);
	//Image::StageRectangle(hdc, box);
}

void Structure::SetStage(Stage* parentStage)
{
	this->parentStage = parentStage;
}

Stage* Structure::GetStage()
{
	return parentStage;
}

void Structure::SetTilePos(POINT tilePos)
{
	this->tilePos = tilePos;
}

POINT Structure::GetTilePos()
{
	return tilePos;
}

void Structure::SetTileFullBox(RECT tileFullBox)
{
	this->tileFullBox = tileFullBox;
}

RECT Structure::GetTileFullBox()
{
	return tileFullBox;
}

void Structure::SetStructureType(int type)
{
	this->type = type;
	StructureInfo* info = GameData::GetSingleton()->GetStructureInfo(type);
	imageRandomFrame = rand() % (info->GetImg()->GetImageInfo()->maxFrameX);
	MakeRecipeList();
}

int Structure::GetStructureType()
{
	return type;
}

void Structure::SetAnchorPos(FPOINT anchor)
{
	StructureInfo* info = GameData::GetSingleton()->GetStructureInfo(type);
	POINT tileSize = info->GetTileSize();

	FPOINT tempSize = FPOINT{
		(float)tileSize.x * Con::TILESIZE,
		(float)tileSize.y * Con::TILESIZE
	};

	FPOINT tempPos = FPOINT{
		anchor.x + (tempSize.x * 0.5f),
		anchor.y - (tempSize.y * 0.5f)
	};

	FPOINT tempOffset = FPOINT{
		-tempSize.x * 0.5f,
		-tempSize.y * 0.5f
	};

	tileFullBox = RECT{
		(LONG)(tempPos.x + tempOffset.x),
		(LONG)(tempPos.y + tempOffset.y),
		(LONG)(tempPos.x + tempOffset.x + tempSize.x),
		(LONG)(tempPos.y + tempOffset.y + tempSize.y)
	};

	tempSize.x -= Con::STRUCTURE_GAP * 2;
	tempSize.y -= Con::STRUCTURE_GAP * 2;

	tempOffset.x += Con::STRUCTURE_GAP;
	tempOffset.y += Con::STRUCTURE_GAP;

	SetSize(tempSize);
	SetPos(tempPos);
	SetOffset(tempOffset);
}

void Structure::MakeRecipeList()
{
	craftingRecipes = GameData::GetSingleton()->GetStructureCraftingRecipes(type);
}

vector<CraftingRecipe*> Structure::GetRecipeList()
{
	return craftingRecipes;
}

CraftingRecipe* Structure::GetCurrRecipe()
{
	if (craftingIdx >= 0 && craftingIdx < craftingRecipes.size())
	{
		return craftingRecipes[craftingIdx];
	}
	else
	{
		return nullptr;
	}
}

void Structure::StartCrafting(int craftingListIdx, int amount)
{
	//크래프팅 시작되면 레시피에 적힌 재료들 개수 * 아웃풋 아이템의 개수만큼 인풋을 받아서 넣는다.
	//크래프팅 하나 완료될 때마다 인풋에서 레시피만큼 빼고 아웃풋을 지정한다.
	//무한 크래프팅 시 인풋을 레시피에 적힌 재료들 개수만큼으로 유지하려 한다.
	//크래프팅 취소 시 모든 인풋을 아이템으로 반환한다.
	if (craftingListIdx < craftingRecipes.size())
	{
		//if (CanCraft(craftingListIdx, amount))
		//{
		//	RemoveCraftingMaterial(craftingListIdx, amount);
		//	craftingIdx = craftingListIdx;
		//	craftingStartTime = TimerManager::GetSingleton()->GetProgramTime();
		//	isCraftingInfinite = false;
		//	craftingInputCount = amount;
		//	craftingOutputCount = 0;
		//}
		craftingIdx = craftingListIdx;
		craftingStartTime = TimerManager::GetSingleton()->GetProgramTime();
		isCraftingInfinite = false;
		craftingInputCount = amount;
		//craftingOutputCount = 0;
	}
}

void Structure::StartCraftingInfinite(int craftingListIdx)
{
	if (craftingListIdx >= 0 && craftingListIdx < craftingRecipes.size())
	{
		craftingIdx = craftingListIdx;
		isCraftingInfinite = true;
		craftingInputCount = 0;
		//craftingOutputCount = 0;

		craftingRequiredItemList.clear();
		for (int i = 0; i < Con::CRAFTING_MATERIAL_MAX; i++)
		{
			craftingRequiredItemList.push_back(craftingRecipes[craftingIdx]->materials[i]);
		}
	}
}

void Structure::CraftingUpdate()
{

	// 인풋이 없고 무한이면 인벤 체크, 인벤에 재료 있으면 털어가고 크래프팅 시작
	// 시간이 다됐으면 현재 크래프팅 완료
	// 인풋이 없고 무한이 아니면 중지
	if (craftingIdx >= 0 && craftingIdx < craftingRecipes.size())
	{
		CraftingRecipe* currRecipe = GetCurrRecipe();
		TimerManager* timerM = TimerManager::GetSingleton();
		if (currRecipe)
		{
			if (craftingInputCount <= 0 && isCraftingInfinite)
			{
				//if (CanCraft(craftingIdx, 1))
				//{
				//	RemoveCraftingMaterial(craftingIdx, 1);
				//	craftingStartTime = timerM->GetProgramTime();
				//	craftingInputCount++;
				//}
			}
			while (craftingStartTime + currRecipe->craftingTime < timerM->GetProgramTime() &&
				craftingInputCount > 0)
			{
				craftingStartTime += currRecipe->craftingTime;
				CompleteCurrCrafting();
			}
		}
	}
}

//bool Structure::CanCraft(int recipeListIdx, int amount)
//{
//	//if (recipeListIdx > -1 && recipeListIdx < craftingRecipes.size())
//	//{
//	//	CraftingRecipe* currRecipe = craftingRecipes[recipeListIdx];
//	//	if (currRecipe)
//	//	{
//	//		for (int i = 0; i < Con::CRAFTING_MATERIAL_MAX; i++)
//	//		{
//	//			Item material = currRecipe->materials[i];
//	//			//Structure에 InventoryContainer 넣기
//	//			if (inventoryContainer->GetItemCount(material.idx) < material.count * amount)
//	//			{
//	//				return false;
//	//			}
//	//		}
//	//		return true;
//	//	}
//	//}
//	//return false;
//}

//bool Structure::RemoveCraftingMaterial(int recipeListIdx, int amount)
//{
//	//if (recipeListIdx < craftingRecipes.size())
//	//{
//	//	for (int i = 0; i < Con::CRAFTING_MATERIAL_MAX; i++)
//	//	{
//	//		Item material = GetCurrRecipe()->materials[i];
//	//		inventoryContainer->RemoveItem(Item{ material.idx, material.count * amount });
//	//	}
//	//	return true;
//	//}
//	//return false;
//}

void Structure::CompleteCurrCrafting()
{
	craftingOutputItemList.push_back(
		Item{ craftingRecipes[craftingIdx]->resultItemIdx, 1 });
	craftingInputCount -= 1;
	//craftingOutputCount += 1;
}

void Structure::StopCrafting()
{
	vector<Item> input = GetCraftingInputs();
	for (int i = 0; i < input.size(); i++) 
	{
		craftingOutputItemList.push_back(input[i]);
	}
	isCraftingInfinite = false;
	craftingInputCount = 0;
}

vector<Item> Structure::GetCraftingInputs()
{
	return GetCraftingMaterials(craftingIdx, craftingInputCount);
}

vector<Item> Structure::GetCraftingMaterials(int recipeListIdx, int amount)
{
	vector<Item> matList;
	if (recipeListIdx >= 0 && recipeListIdx < craftingRecipes.size() &&
		amount > 0)
	{
		CraftingRecipe* currRecipe = craftingRecipes[recipeListIdx];
		for (int i = 0; i < Con::CRAFTING_MATERIAL_MAX; i++)
		{
			Item material = currRecipe->materials[i];
			if (material.idx != GameData::EMPTY_ITEM.idx)
			{
				material.count = material.count * amount;
				matList.push_back(material);
			}
		}
	}
	return matList;
}

//Item Structure::GetCraftingOutput()
//{
//	//CraftingRecipe* currRecipe = craftingRecipes[craftingIdx];
//	//Item result = Item{ currRecipe->resultItemIdx, craftingInputCount };
//	//return result;
//}

vector<Item> Structure::GetDrops()
{
	return GameData::GetSingleton()->GetStructureInfo(type)->GetDrops();
}
