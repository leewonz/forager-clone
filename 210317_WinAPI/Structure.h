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
	// ũ������ ���� ��ư �������� ����
	void StartCrafting(int recipeListIdx, int amount);
	// ũ������ �ѹ� ���� ��ư �������� ����
	void StartCraftingInfinite(int recipeListIdx);
	// �������� ũ������ �߿� ��ᰡ �� ������ ����
	void ResumeCraftingInfinite();
	// �Ź� ũ������ �����Ұ�
	void CraftingUpdate();
	// �κ��� ũ������ ��� �ִ°�?
	//bool CanCraft(int recipeListIdx, int amount);
	// �κ����� ũ������ ��� ����
	//bool RemoveCraftingMaterial(int recipeListIdx, int amount);
	// ũ������ ��� ���� ���̰�, ��� ���� �ø�
	void CompleteCurrCrafting();
	// ���� �������� ũ�������� ������ ���߰� ��� ������ ��ȯ
	void StopCrafting();
	// ���� ��� ������ ��ȯ
	vector<Item> GetCraftingInputs();
	// Ư�� �������� ��� �� ��ȯ
	vector<Item> GetCraftingMaterials(int recipeListIdx, int amount);
	// ��� ������ ��ȯ
	//Item GetCraftingOutput();
	// ��� ������ ���� ����
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

