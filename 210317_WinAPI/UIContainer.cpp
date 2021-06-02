#include "UIContainer.h"
#include "image.h"
#include "CommonFunction.h"

HRESULT UIContainer::Init()
{
	SetPos(FPOINT{ 0.0f, 0.0f });
	tabImg = ImageManager::GetSingleton()->FindImage("ui_menuTab3");
	tabSize = POINT{ tabImg->GetWidth(), tabImg->GetHeight() };
	tabRect = RECT{ (LONG)TAB_POS.x, (LONG)TAB_POS.y,
		(LONG)(TAB_POS.x + (tabSize.x * TAB_SCALE)), (LONG)(TAB_POS.y + (tabSize.y * TAB_SCALE)) };
	SetActiveTab(0);
	return S_OK;
}

void UIContainer::Release()
{
	for (int i = 0; i < children.size(); i++)
	{
		SAFE_RELEASE(children[i]);
	}
}

void UIContainer::AddChild(UIObject* uiObject)
{
	children.push_back(uiObject);
	children[children.size() - 1]->SetActive((children.size() - 1) == currActiveTab);
}

void UIContainer::SetActiveTab(int tabNum)
{
	currActiveTab = tabNum;
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i])
		{
			children[i]->SetActive(i == currActiveTab);
		}
	}
}

pair<UI_MESSAGE, int> UIContainer::MouseDown(POINT mousePos)
{
	pair<UI_MESSAGE, int> childMessage = { UI_MESSAGE::NONE, 0 };
	RECT tabBox = RECT{ (LONG)pos.x + tabRect.left, (LONG)pos.y + tabRect.top,
						(LONG)pos.x + tabRect.right, (LONG)pos.y + tabRect.bottom };

	if (PointInRect(mousePos, tabBox))
	{
		int tabNum = (mousePos.x - tabBox.left) / ((tabBox.right - tabBox.left) / TAB_COUNT);

		if (tabNum >= 0 && tabNum < children.size())
		{
			SetActiveTab(tabNum);
		}
	}

	if (isActive)
	{
		bool isEnded = false;
		for (int i = 0; i < children.size(); i++)
		{
			switch (childMessage.first)
			{
			case UI_MESSAGE::BLOCKED:
			case UI_MESSAGE::OK:
				isEnded = true;
				break;
			}

			if (isEnded) { return childMessage; }

			if (children[i]->GetActive())
			{
				childMessage = children[i]->MouseDown(mousePos);
			}
		}
	}

	return childMessage;
}

pair<UI_MESSAGE, int> UIContainer::MouseUp(POINT mousePos)
{
	pair<UI_MESSAGE, int> childMessage = { UI_MESSAGE::NONE, 0 };

	if (isActive)
	{
		bool isEnded = false;
		for (int i = 0; i < children.size(); i++)
		{
			switch (childMessage.first)
			{
			case UI_MESSAGE::BLOCKED:
			case UI_MESSAGE::OK:
				isEnded = true;
				break;
			}

			if (isEnded) { break; }

			if (children[i]->GetActive())
			{
				childMessage = children[i]->MouseUp(mousePos);
			}
		}
	}

	return childMessage;
}

pair<UI_MESSAGE, int> UIContainer::Back()
{
	pair<UI_MESSAGE, int> childMessage = { UI_MESSAGE::NONE, 0 };

	if (isActive)
	{
		bool isEnded = false;
		for (int i = 0; i < children.size(); i++)
		{
			switch (childMessage.first)
			{
			case UI_MESSAGE::BACK:
				isEnded = true;
				break;
			}

			if (isEnded) { break; }

			if (children[i]->GetActive())
			{
				childMessage = children[i]->Back();
			}
		}

		if (childMessage.first == UI_MESSAGE::NONE)
		{
			childMessage = { UI_MESSAGE::BACK, 0 };
			SetActive(false);
		}
	}

	return childMessage;
}

void UIContainer::OnActivate()
{
}

void UIContainer::OnDeactivate()
{
}

void UIContainer::Render(HDC hdc)
{
	if (isActive)
	{
		RECT tabBox = RECT{ (LONG)pos.x + tabRect.left, (LONG)pos.y + tabRect.top,
							(LONG)pos.x + tabRect.right, (LONG)pos.y + tabRect.bottom };
		tabImg->Render(hdc, tabBox.left, tabBox.top, TAB_SCALE, false);

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Render(hdc);
		}
	}
}
