#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"
#include "Stage.h"
#include "Camera.h"

HRESULT TilemapTool::Init()
{
    Camera* cam = Camera::GetSingleton();
    cam->SetScreenSize(POINT{ TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y });

    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    sampleTile = ImageManager::GetSingleton()->FindImage("sampleTile");

    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    // ���� ���� ��Ʈ ����
    stage = new Stage();
    stage->Init(POINT{ Con::TILESIZE, Con::TILESIZE });

    // ���� ���� ��Ʈ ����
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile,
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (Con::TILESIZE * j),
                (Con::TILESIZE * i),
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (Con::TILESIZE * j) + Con::TILESIZE,
                (Con::TILESIZE * i) + Con::TILESIZE);

            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left =
            //    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (Con::TILESIZE * j);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top = (Con::TILESIZE * i);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.right =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left + Con::TILESIZE;
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.bottom =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top + Con::TILESIZE;
        }
    }

    // UI Button
    ImageManager::GetSingleton()->AddImage("�����ư", "Image/button.bmp",
        122, 62, 1, 2);
    ImageManager::GetSingleton()->AddImage("�ҷ������ư", "Image/button.bmp",
        122, 62, 1, 2);

    //btnSave = new Button();
    //btnSave->Init("�����ư", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() - 200,
    //    TILEMAPTOOLSIZE_Y - 200);
    //btnSave->SetFunc(Save, 1);

    //btnLoad = new Button();
    //btnLoad->Init("�ҷ������ư", TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
    //    TILEMAPTOOLSIZE_Y - 200);
    //btnLoad->SetFunc(Load, 1);

    return S_OK;
}

void TilemapTool::Release()
{
    SAFE_RELEASE(btnSave);
    SAFE_RELEASE(btnLoad);
    SAFE_RELEASE(stage);
}

void TilemapTool::Update()
{
    Camera* cam = Camera::GetSingleton();
    FPOINT worldSpaceMouse = cam->CameraToWorld(toFpoint(g_ptMouse));
    TimerManager* timerManager = TimerManager::GetSingleton();
    // ���̺� F1 F2 F3 ...
    //int stageNum = VK_F1;
    //int currInputKey;

    if (btnSave)    btnSave->Update();
    if (btnLoad)    btnLoad->Update();

    stage->Update();

    // ���� ���� ���
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = rcMain.left + (Con::TILESIZE * Con::TILE_X);
    rcMain.bottom = rcMain.top + (Con::TILESIZE * Con::TILE_Y);

    // ���� ���� ���
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    if (PtInRect(&rcSample, g_ptMouse))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            // 2) ���콺 ��ǥ�� �ε��� ���
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptStartSelectedFrame.x = posX / Con::TILESIZE;
            ptStartSelectedFrame.y = posY / Con::TILESIZE;

            ptSelected[0] = g_ptMouse;

            //// 1) ��� Ÿ���� �ݺ��ϸ鼭 ��Ʈ�浹 Ȯ��
            //for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
            //{
            //    if (PtInRect(&(sampleTileInfo[i].rcTile), g_ptMouse))
            //    {
            //        ptStartSelectedFrame.x = i % SAMPLE_TILE_X;
            //        ptStartSelectedFrame.y = i / SAMPLE_TILE_X;

            //        break;
            //    }
            //}
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptEndSelectedFrame.x = posX / Con::TILESIZE;
            ptEndSelectedFrame.y = posY / Con::TILESIZE;

            // ���ÿ��� �ʱ�ȭ
            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            ptSelected[1] = g_ptMouse;
        }
    }
    else if (PtInRect(&rcMain, toPoint(worldSpaceMouse)))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            POINT selMainTileIdx =stage->PosToTile(worldSpaceMouse);

            stage->ChangeTerrain(
                selMainTileIdx,
                (TerrainType)ptStartSelectedFrame.x,
                ptStartSelectedFrame.y == 0 ? true : false);
        }
    }
    

    if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
    {
        SceneManager::GetSingleton()->ChangeScene("����_1");
    }

    if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
    {
        FPOINT camCenter = cam->GetPosCenter();
        cam->SetPosCenter(FPOINT{ camCenter.x, camCenter.y - (timerManager->GetElapsedTime() * 200.0f)});
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
    {
        FPOINT camCenter = cam->GetPosCenter();
        cam->SetPosCenter(FPOINT{ camCenter.x - (timerManager->GetElapsedTime() * 200.0f), camCenter.y });
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
    {
        FPOINT camCenter = cam->GetPosCenter();
        cam->SetPosCenter(FPOINT{ camCenter.x, camCenter.y + (timerManager->GetElapsedTime() * 200.0f) });
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
    {
        FPOINT camCenter = cam->GetPosCenter();
        cam->SetPosCenter(FPOINT{ camCenter.x + (timerManager->GetElapsedTime() * 200.0f), camCenter.y });
    }

    return;
}

void TilemapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,
        TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // ����Ÿ�� ��ü
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    // ���� ���� ǥ��
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    // UI Button
    if (btnSave)    btnSave->Render(hdc);
    if (btnLoad)    btnLoad->Render(hdc);

    // ���ο��� ��ü
    //for (int i = 0; i < TILE_X * TILE_Y; i++)
    //{
    //    sampleTile->FrameRender(hdc,
    //        tileInfo[i].rcTile.left,
    //        tileInfo[i].rcTile.top,
    //        tileInfo[i].frameX,
    //        tileInfo[i].frameY);
    //}
    stage->Render(hdc);

    // ���õ� Ÿ��
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
        ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        sampleTile->FrameRender(hdc,
            TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
            sampleTile->GetHeight() + 50,
            ptStartSelectedFrame.x, ptStartSelectedFrame.y, false, 3);
    }
    else
    {
        for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
        {
            for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
            {
                sampleTile->FrameRender(hdc,
                    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * Con::TILESIZE),
                    sampleTile->GetHeight() + 50 + (i * Con::TILESIZE),
                    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);

            }
        }
    }

}

/*
    �ǽ�1. F1, F2, F3  �� Ű�� ������ �� 
    Save/saveMapData1.map, Save/saveMapData2.map, Save/saveMapData3.map
    �� �� ���Ͽ� ����� �� �ֵ��� �ڵ� ����

    �ǽ�2. �ε�� Ctrl + F1, ... 
*/
