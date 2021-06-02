#pragma once
#include "UIObject.h"
#include "config.h"

class Image;
class UIContainer : public UIObject
{
private:
	const int TAB_COUNT = 3;
	const float TAB_SCALE = 2.0f;
	const POINT TAB_POS = POINT{500, 32};

	vector<UIObject*> children;
	Image* tabImg;
	POINT tabSize;
	RECT tabRect;
	int currActiveTab = 0;

public:
	HRESULT Init();
	void Release();

	void AddChild(UIObject* uiObject);
	void SetActiveTab(int tabNum);

	virtual pair<UI_MESSAGE, int> MouseDown(POINT mousePos);
	virtual pair<UI_MESSAGE, int> MouseUp(POINT mousePos);
	virtual pair<UI_MESSAGE, int> Back();
	virtual void OnActivate();
	virtual void OnDeactivate();

	void Render(HDC hdc);
};

