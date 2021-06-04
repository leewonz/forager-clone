#pragma once

#include "StageObject.h"
#include "GameData.h"

class Stage;
class Image;
class InventoryContainer;
class Structure : public StageObject
{
	Stage* parentStage;
	Image* progressCircleImg;
	InventoryContainer* inventoryContainer;
	//GameScene* gameScene;
	POINT tilePos;
	int type;
	RECT tileFullBox;
	int imageRandomFrame = 0;

	int craftingIdx = -1;
	float craftingStartTime = 0.0f;
	int craftingInputCount;
	//int craftingOutputCount;
	vector<Item> craftingRequiredItemList;
	vector<Item> craftingOutputItemList;
	bool isCraftingInfinite;
	vector<CraftingRecipe*> craftingRecipes;

public:
	virtual HRESULT Init(Stage* parentStage);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetStage(Stage* parentStage);
	Stage* GetStage();

	inline void SetInventoryContainer(InventoryContainer* inventoryContainer) 
		{ this->inventoryContainer = inventoryContainer; }
	inline InventoryContainer* GetInventoryContainer()
		{ return inventoryContainer; }

	void SetTilePos(POINT tilePos);
	POINT GetTilePos();
	void SetTileFullBox(RECT tileFullBox);
	RECT GetTileFullBox();
	void SetStructureType(int type);
	int GetStructureType();
	void SetAnchorPos(FPOINT anchor);
	void MakeRecipeList();
	vector<CraftingRecipe*> GetRecipeList();
	CraftingRecipe* GetCurrRecipe();
	// 크래프팅 시작 버튼 눌렀을때 실행
	void StartCrafting(int recipeListIdx, int amount);
	// 크래프팅 한무 시작 버튼 눌렀을때 실행
	void StartCraftingInfinite(int recipeListIdx);
	// 무한으로 크래프팅 중에 재료가 들어갈 때마다 실행
	void ResumeCraftingInfinite();
	// 매번 크래프팅 실행할거
	void CraftingUpdate();
	// 인벤에 크래프팅 재료 있는가?
	//bool CanCraft(int recipeListIdx, int amount);
	// 인벤에서 크래프팅 재료 삭제
	//bool RemoveCraftingMaterial(int recipeListIdx, int amount);
	// 크래프팅 재료 개수 줄이고, 결과 개수 올림
	void CompleteCurrCrafting();
	// 현재 진행중인 크래프팅을 강제로 멈추고 재료 아이템 반환
	void StopCrafting();
	// 넣은 재료 아이템 반환
	vector<Item> GetCraftingInputs();
	// 특정 레시피의 재료 수 반환
	vector<Item> GetCraftingMaterials(int recipeListIdx, int amount);
	// 결과 아이템 반환
	//Item GetCraftingOutput();
	// 결과 아이템 개수 설정
	//inline void SetCraftingOutputCount(int count) { this->craftingOutputCount = count; }
	vector<Item> GetDrops();

	inline bool GetCraftingInputCount() { return craftingInputCount; }
	inline void SetCraftingInputCount(int count) { craftingInputCount = count; }
	inline vector<Item> GetCraftingRequiredItems() { return craftingRequiredItemList; }
	inline void ResetCraftingRequiredItems() { craftingRequiredItemList.clear(); }
	inline vector<Item> GetCraftingOutputItems() { return craftingOutputItemList; }
	inline void ResetCraftingOutputItems() { craftingOutputItemList.clear(); }
	inline bool GetIsCraftingInfinite() { return isCraftingInfinite; }
};

