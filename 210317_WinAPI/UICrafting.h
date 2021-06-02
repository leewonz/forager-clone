#pragma once
#include "UIObject.h"
class Image;
class InventoryContainer;
class DropContainer;
class Structure;
class UICrafting :
    public UIObject
{
	struct CraftingButton
	{
		int idx;
		RECT box;
	};
	vector<CraftingButton> craftingButtons;

	const int BUTTON_GAP = 6;
	const POINT BUTTON_ICON_OFFSET = POINT{ 16, 16 };
	const float BUTTON_SCALE = 2.0f;
	const int BUTTON_MAX_COUNT = 100;

	Image* buttonImg;
	Image* bgImg;
	Image* arrowImg;
	InventoryContainer* inventoryContainer;
	DropContainer* dropContainer;
	Structure* structure;

	POINT buttonSize;
	POINT resultBGPoint;
	POINT craftButtonPoint;
	POINT craftInfiniteButtonPoint;
	int selectedRecipe = -1;

	char szText[128] = "";

public:
	HRESULT Init();
	void Render(HDC hdc);

	virtual pair<UI_MESSAGE, int> MouseDown(POINT mousePos);
	virtual pair<UI_MESSAGE, int> MouseUp(POINT mousePos);
	virtual pair<UI_MESSAGE, int> Back();
	virtual void OnActivate();
	virtual void OnDeactivate();

	inline void SetInventoryContainer(InventoryContainer* container) { this->inventoryContainer = container; }
	inline void SetDropContainer(DropContainer* container) { this->dropContainer = container; }
	inline void SetStructure(Structure* structure) { this->structure = structure; }
};

