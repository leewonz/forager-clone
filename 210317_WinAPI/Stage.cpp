#include "Stage.h"
#include "TerrainInfo.h"
#include "Structure.h"
#include "StructureInfo.h"

HRESULT Stage::Init(POINT tileSize)
{
    InitInfo();
    for (int y = 0; y < Con::TILE_Y; y++)
    {
        for (int x = 0; x < Con::TILE_X; x++)
        {
            //Terrain* tempTerrain = new Terrain();
            terrainTiles[y][x].Init(this);
            terrainTiles[y][x].SetTerrainType(TerrainType::GRASS);
            terrainTiles[y][x].SetIsLand(true);
            terrainTiles[y][x].SetPos(
                FPOINT{ (float)(tileSize.x * x) + tileSize.x * 0.5f,
                        (float)(tileSize.y * y) + tileSize.y * 0.5f });
            terrainTiles[y][x].SetOffset(
                FPOINT{ -tileSize.x * 0.5f , -tileSize.y * 0.5f });
            terrainTiles[y][x].SetSize(
                FPOINT{ (float)tileSize.x , (float)tileSize.y });
        }
    }

    RefreshTileShapeAll();

    return S_OK;
}

void Stage::Release()
{
    for (int i = 0; i < structures.size(); i++)
    {
        SAFE_RELEASE(structures[i]);
    }
    for (int i = 0; i < structureInfos.size(); i++)
    {
        SAFE_DELETE(structureInfos[i]);
    }
    for (int i = 0; i < terrainInfos.size(); i++)
    {
        SAFE_DELETE(terrainInfos[i]);
    }
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

    /*for(structure structures*/
}

void Stage::Render(HDC hdc)
{
    for (int y = 0; y < Con::TILE_Y; y++)
    {
        for (int x = 0; x < Con::TILE_X; x++)
        {
            terrainTiles[y][x].Render(hdc);
        }
    }
    for (int i = 0; i < structures.size(); i++)
    {
        structures[i]->Render(hdc);
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
    EncodeTerrain();
    WriteFile(hFile, this->code, sizeof(int) * Con::TILE_X * Con::TILE_Y,
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

    if (ReadFile(hFile, this->code, sizeof(int) * Con::TILE_X * Con::TILE_Y,
        &readBytes, NULL))
    {
        DecodeTerrain(this->code);
    }
    else
    {
        MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
    }
    HRESULT err = GetLastError();
    int errInt = (int)err;

    CloseHandle(hFile);
}

int* Stage::EncodeTerrain()
{
    int* code;
    code = new int[Con::TILE_Y * Con::TILE_X];

    for (int y = 0; y < Con::TILE_Y; y++)
    {
        for (int x = 0; x < Con::TILE_X; x++)
        {
            int currCode = 0;
            currCode += (int)terrainTiles[y][x].GetTerrainType();
            currCode += terrainTiles[y][x].GetIsLand() ? (int)TerrainType::END : 0;
            this->code[y * Con::TILE_X + x] = currCode;
        }
    }
    return code;
}

void Stage::DecodeTerrain(int* code)
{
    for (int y = 0; y < Con::TILE_Y; y++)
    {
        for (int x = 0; x < Con::TILE_X; x++)
        {
            int currCode = this->code[y * Con::TILE_X + x];
            terrainTiles[y][x].SetTerrainType(
                (TerrainType)(currCode % (int)TerrainType::END));
            terrainTiles[y][x].SetIsLand(
                (currCode / (int)TerrainType::END) == 1 ? true : false);
            terrainTiles[y][x].SetIsFree(terrainTiles[y][x].GetIsLand());
            terrainTiles[y][x].SetStage(this);
        }
    }

    RefreshTileShapeAll();
}

bool Stage::CanBuild(RECT region)
{
    for (int y = region.top; y <= region.bottom; y++)
    {
        for (int x = region.left; x <= region.right; x++)
        {
            if (!IsInStage(POINT{x, y}))
            {
                return false;
            }

            else if (terrainTiles[y][x].GetIsFree() == false)
            {
                return false;
            }
        }
    }
    return true;
}

bool Stage::BuildStructure(POINT tilePos, int typeIdx)
{
    // 1. 건물 종류를 받아온다.
    StructureInfo* tempInfo = GetStructureInfo(typeIdx);

    // 2. 건물이 설치 가능한지 확인한다.
    POINT tileSize = tempInfo->GetTileSize();
    RECT tileRect =
        RECT{ tilePos.x, tilePos.y - tileSize.y + 1,
        tilePos.x + tileSize.x - 1, tilePos.y };
    POINT selectedTile = { tilePos.x , tilePos.y };
    if (!CanBuild(tileRect))
    {
        return false;
    }
    else
    {
        // 3. 건물을 만들고 세팅
        Structure* tempStr = new Structure();
        tempStr->Init(this);
        tempStr->SetStructureType(typeIdx);

        FPOINT anchor = TileToPos(tilePos);
        anchor.y += Con::TILESIZE;
        FPOINT size = FPOINT{
            (float)tileSize.x * Con::TILESIZE,
            (float)tileSize.y * Con::TILESIZE
        };
        FPOINT pos = anchor;
        pos.x += size.x * 0.5f;
        pos.y -= size.y * 0.5f;
        FPOINT offset = FPOINT{
            -size.x * 0.5f,
            -size.y * 0.5f
        };
        tempStr->SetPos(pos);
        tempStr->SetSize(size);
        tempStr->SetOffset(offset);

        // 4. 만들어진 건물이 있는 Terrain 타일을 막혀있다고 세팅힌다.
        for (int y = tileRect.top; y <= tileRect.bottom; y++)
        {
            for (int x = tileRect.left; x <= tileRect.right; x++)
            {
                terrainTiles[y][x].SetIsFree(false);
            }
        }

        // 5. 건물을 벡터에 넣기
        structures.push_back(tempStr);
        GetTerrain(selectedTile)->SetStructure(tempStr);
        return true;
    }
}

void Stage::RefreshTileShapeAll()
{
    for (int y = 0; y < Con::TILE_Y; y++)
    {
        for (int x = 0; x < Con::TILE_X; x++)
        {
            terrainTiles[y][x].RefreshTileShape();
        }
    }
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
        terrainInfos.push_back(tempTerrainInfo);
    }
    StructureInfo* tempStructureInfo = new StructureInfo();
    tempStructureInfo->Init(0, "sampleBuilding", "sampleBuilding");
    tempStructureInfo->SetTileSize(POINT{ 2, 2 });
    structureInfos.push_back(tempStructureInfo);

    adjTileShape[0] = { 0,0 };
    adjTileShape[AdjDirs::R] = { 0,3 };
    adjTileShape[AdjDirs::D] = { 1,3 };
    adjTileShape[AdjDirs::L] = { 2,3 };
    adjTileShape[AdjDirs::U] = { 3,3 };
    adjTileShape[AdjDirs::R + AdjDirs::U] = { 3,2 };
    adjTileShape[AdjDirs::D + AdjDirs::R] = { 2,2 };
    adjTileShape[AdjDirs::L + AdjDirs::D] = { 1,2 };
    adjTileShape[AdjDirs::L + AdjDirs::U] = { 0,2 };
    adjTileShape[AdjDirs::L + AdjDirs::R] = { 4,2 };
    adjTileShape[AdjDirs::D + AdjDirs::U] = { 4,3 };
    adjTileShape[AdjDirs::D + AdjDirs::L + AdjDirs::U] = { 0,1 };
    adjTileShape[AdjDirs::L + AdjDirs::R + AdjDirs::U] = { 1,1 };
    adjTileShape[AdjDirs::R + AdjDirs::D + AdjDirs::U] = { 2,1 };
    adjTileShape[AdjDirs::L + AdjDirs::D + AdjDirs::R] = { 3,1 };
    adjTileShape[AdjDirs::L + AdjDirs::D + AdjDirs::R + AdjDirs::U] = { 1,0 };
    adjTileShapeWater[0] = { 3,0 };
    adjTileShapeWater[1] = { 2,0 };
}

Terrain* Stage::GetTerrain(POINT TilePos)
{
    return &terrainTiles[TilePos.y][TilePos.x];
}

TerrainInfo* Stage::GetTerrainInfo(TerrainType i)
{
    return terrainInfos[(int)i];
}

StructureInfo* Stage::GetStructureInfo(int i)
{
    return structureInfos[i];
}

void Stage::ChangeTerrain(POINT posIdx, TerrainType type, bool isLand)
{
    terrainTiles[posIdx.y][posIdx.x].SetIsLand(isLand);
    terrainTiles[posIdx.y][posIdx.x].SetTerrainType(type);
    for (int y = posIdx.y - 1; y <= posIdx.y + 1; y++)
    {
        for (int x = posIdx.x - 1; x <= posIdx.x + 1; x++)
        {
            if (IsInStage(POINT{x, y}))
            {
                terrainTiles[y][x].RefreshTileShape();
            }
        }
    }
}
