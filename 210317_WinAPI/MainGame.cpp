#include "MainGame.h"
#include "Image.h"
#include "TilemapTool.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Camera.h"
#include "GameData.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	srand(time(NULL));

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	Camera::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	GameData::GetSingleton()->Init();
	Image::SetCamera(Camera::GetSingleton());

	// 메인게임의 초기화 함수
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// 백버퍼 이미지
	int maxWidth, maxHeight;
	maxWidth = max(WINSIZE_X, GAMESCENESIZE_X);
	maxHeight = max(WINSIZE_Y, GAMESCENESIZE_Y);

	backBuffer = new Image();
	backBuffer->Init(maxWidth, maxHeight);

	SceneManager::GetSingleton()->AddScene("전투_1", new GameScene());
	SceneManager::GetSingleton()->AddScene("타일맵툴", new TilemapTool());
	SceneManager::GetSingleton()->AddScene("타이틀", new TitleScene());
	//SceneManager::GetSingleton()->AddScene("A*", new AstarScene());	

	SceneManager::GetSingleton()->ChangeScene("타이틀");

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();

	SAFE_RELEASE(backBuffer);

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	Image::SetCameraStatus(Camera::GetSingleton());
	SceneManager::GetSingleton()->Render(hBackDC);

	// 인사
	//TextOut(hBackDC, 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	// 마우스 좌표
	wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x, g_ptMouse.y);
	//TextOut(hBackDC, 20, 20, szText, strlen(szText));
	// FPS
	// 시간
	//wsprintf(szText, "TIME : %d", (int)(TimerManager::GetSingleton()->GetProgramTime()));
	//TextOut(hBackDC, 20, 20, szText, strlen(szText));
	TimerManager::GetSingleton()->Render(hBackDC);

	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
