#include "TitleScene.h"
#include "config.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT TitleScene::Init()
{
    SetClientRect(g_hWnd, TITLESCENESIZE_X, TITLESCENESIZE_Y);

    titleImg = ImageManager::GetSingleton()->FindImage("title");
    buttonImg = ImageManager::GetSingleton()->FindImage("ui_button");

    gameButtonRect = RECT{
        (LONG)((TITLESCENESIZE_X / 2) - 100 - (buttonImg->GetImageInfo()->frameWidth * BUTTON_SIZE)),
        (LONG)((TITLESCENESIZE_Y / 2) + 200),
        (LONG)((TITLESCENESIZE_X / 2) - 100),
        (LONG)((TITLESCENESIZE_Y / 2) + 200 + (buttonImg->GetImageInfo()->frameHeight * BUTTON_SIZE))
    };
    mapToolButtonRect = RECT{
        (LONG)((TITLESCENESIZE_X / 2) + 100),
        (LONG)((TITLESCENESIZE_Y / 2) + 200),
        (LONG)((TITLESCENESIZE_X / 2) + 100 + (buttonImg->GetImageInfo()->frameWidth * BUTTON_SIZE)),
        (LONG)((TITLESCENESIZE_Y / 2) + 200 + (buttonImg->GetImageInfo()->frameHeight * BUTTON_SIZE))
    };
    return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
    {
        if (PointInRect(g_ptMouse, gameButtonRect))
        {
            SceneManager::GetSingleton()->ChangeScene("전투_1");
        }
        if (PointInRect(g_ptMouse, mapToolButtonRect))
        {
            SceneManager::GetSingleton()->ChangeScene("타일맵툴");
        }
    }
}

void TitleScene::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,
        TITLESCENESIZE_X, TITLESCENESIZE_Y, WHITENESS);
    titleImg->Render(hdc, 0, 0, false);
    buttonImg->Render(hdc, gameButtonRect.left, gameButtonRect.top, BUTTON_SIZE, false);
    buttonImg->Render(hdc, mapToolButtonRect.left, mapToolButtonRect.top, BUTTON_SIZE, false);
}
