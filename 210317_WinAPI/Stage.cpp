#include "Stage.h"


#include "TerrainInfo.h"

HRESULT Stage::Init(POINT tileSize)
{
    InitInfo();
    for (int y = 0; y < TILE_Y; y++)
    {
        for (int x = 0; x < TILE_X; x++)
        {
            //Terrain* tempTerrain = new Terrain();
            TerrainTiles[y][x].Init(this);
            TerrainTiles[y][x].SetTerrainType(TerrainType::GRASS);
            TerrainTiles[y][x].SetIsLand(true);
            TerrainTiles[y][x].SetPos(
                FPOINT{ (float)(tileSize.x * x), (float)(tileSize.y * y) });
            
        }
    }
    return S_OK;
}

void Stage::Release()
{
}

void Stage::Update()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Load();
        }
    }
    else
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Save();
        }
    }
}

void Stage::Render(HDC hdc)
{
    for (int y = 0; y < TILE_Y; y++)
    {
        for (int x = 0; x < TILE_X; x++)
        {
            TerrainTiles[y][x].Render(hdc);
        }
    }
}

void Stage::Save()
{
    string fileName = "Save/saveMapData";  // 1.map";
    //fileName += to_string(stageNum) + ".map";
    fileName += ".map";

    DWORD writtenBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0,
        0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, TerrainTiles, sizeof(Terrain) * TILE_X * TILE_Y,
        &writtenBytes, NULL);

    CloseHandle(hFile);
}

void Stage::Load()
{
    string fileName = "Save/saveMapData";  // 1.map";
    //fileName += to_string(stageNum) + ".map";
    fileName += ".map";

    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, TerrainTiles, sizeof(Terrain) * TILE_X * TILE_Y,
        &readBytes, NULL))
    {
    }
    else
    {
        MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
    }

    for (int y = 0; y < TILE_Y; y++)
    {
        for (int x = 0; x < TILE_X; x++)
        {
            TerrainTiles[y][x].SetStage(this);
        }
    }

    CloseHandle(hFile);
}

void Stage::InitInfo()
{
    for (int i = 0; i < (int)TerrainType::END; i++)
    {
        TerrainInfo* tempTerrainInfo = new TerrainInfo();
        switch ((TerrainType)i)
        {
        case TerrainType::GRASS:
            tempTerrainInfo->Init(i, "tile_grass");
            break;
        case TerrainType::DESERT:
            tempTerrainInfo->Init(i, "tile_desert");
            break;
        case TerrainType::WINTER:
            tempTerrainInfo->Init(i, "tile_winter");
            break;
        case TerrainType::GRAVEYARD:
            tempTerrainInfo->Init(i, "tile_graveyard");
            break;
        case TerrainType::FIRE:
            tempTerrainInfo->Init(i, "tile_fire");
            break;
        }
        TerrainInfos.push_back(tempTerrainInfo);
    }
}

TerrainInfo* Stage::GetTerrainInfo(TerrainType i)
{
    return TerrainInfos[(int)i];
}

void Stage::ChangeTerrain(POINT posIdx, TerrainType type, bool isLand)
{
    TerrainTiles[posIdx.y][posIdx.x].SetIsLand(isLand);
    TerrainTiles[posIdx.y][posIdx.x].SetTerrainType(type);
}
