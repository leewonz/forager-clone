// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

namespace Con
{
	const int TILE_X = 20; //84
	const int TILE_Y = 20; //84
	const int TILESIZE = 16; // 16

	const float CAM_MOUSE_FOLLOW_SCALE = 0.1f;
	const float CAM_SMOOTH_SPEED = 12.0f;

	const int INVEN_PLAYER_X = 8;
	const int INVEN_PLAYER_Y = 5;
	const int INVEN_VAULT_COUNT = 100;
	const int INVEN_VAULT_X = 3;
	const int INVEN_VAULT_Y = 3;

	const float REGEN_RESOURCE_INTERVAL = 5.0f;
	const int REGEN_RESOURCE_COUNT = 3;
}
// 샘플 타일 정보
// 640 * 288
#define SAMPLE_TILE_X	20
#define SAMPLE_TILE_Y	9
//#define TILESIZE		20

// 메인 그리기 공간 정보
//#define	TILE_X			20
//#define	TILE_Y			20

#define WINSIZE_X	1080
#define WINSIZE_Y	720
#define TILEMAPTOOLSIZE_X	1024
#define TILEMAPTOOLSIZE_Y	900
#define GAMESCENESIZE_X		1080
#define GAMESCENESIZE_Y		720
#define ASTARSIZE_X	1620
#define ASTARSIZE_Y	900

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

extern POINT TileSize;
