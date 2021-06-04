#pragma once
#include "UIObject.h"
#include "GameData.h"

class Stage;
class InventoryContainer;
class Image;
class GameScene;
class UIConstruction :
    public UIObject
{
private:
	struct ConstructionButton
	{
		int idx;
		RECT box;
	};
	vector<ConstructionButton> constructionButtons;

	const int BUTTON_GAP = 6;
	const POINT BUTTON_ICON_OFFSET = POINT{ 16, 48 };
	const float BUTTON_SCALE = 2.0f;

	Image* buttonImg;
	Image* bgImg;
	Image* selection1x1Img;
	Image* selection2x2Img;
	Stage* stage;
	InventoryContainer* container;
	
	POINT buttonSize;
	int selectedConstuction = -1;

	char szText[128] = "";

public:
	HRESULT Init();
	void Render(HDC hdc);

	virtual pair<UI_MESSAGE, int> MouseDown(POINT mousePos);
	virtual pair<UI_MESSAGE, int> MouseUp(POINT mousePos);
	virtual pair<UI_MESSAGE, int> Back();
	virtual void OnActivate();
	virtual void OnDeactivate();

	bool IsMaterialEnough(Item* items, int size);
	void RemoveMaterial(Item* items, int size);

	inline void SetStage(Stage* stage) { this->stage = stage; }
	inline void SetInventoryContainer(InventoryContainer* container) { this->container = container; }

	RECT GetTileRect(FPOINT worldMousePos, POINT tileSize);
};

