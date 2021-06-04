#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
    ImageManager::GetSingleton()->AddImage("sampleTile",
        "Image/sampleTile.bmp", 80, 32, 5, 2,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_grass",
        "Image/tile/tile_grass.bmp", 80, 64, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_desert",
        "Image/tile/tile_desert.bmp", 80, 64, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_winter",
        "Image/tile/tile_winter.bmp", 80, 64, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_fire",
        "Image/tile/tile_fire.bmp", 80, 64, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_graveyard",
        "Image/tile/tile_graveyard.bmp", 80, 64, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_furnace",
        "Image/structure/furnace.bmp", 30, 42, 
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_forge",
        "Image/structure/forge.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_sewingStation",
        "Image/structure/sewingStation.bmp", 32, 48,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_tree_grass",
        "Image/structure/tree_grass.bmp", 16, 48,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_tree_fire",
        "Image/structure/tree_fire.bmp", 16, 48,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_tree_snow",
        "Image/structure/tree_snow.bmp", 16, 48,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_tree_desert",
        "Image/structure/tree_desert.bmp", 48, 48,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_stone",
        "Image/structure/stone.bmp", 32, 17, 2, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_coal",
        "Image/structure/coal.bmp", 32, 17, 2, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_iron",
        "Image/structure/iron.bmp", 32, 17, 2, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("structure_gold",
        "Image/structure/gold.bmp", 32, 17, 2, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("item_noneItem",
        "Image/item/noneItem.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("item_bone",
        "Image/item/bone.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("item_stone",
        "Image/item/stone.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("item_flower",
        "Image/item/flower.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("item_wood",
        "Image/item/wood.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("item_coal",
        "Image/item/coal.bmp", 32, 32,
        true, RGB(255, 0, 255));
    
    ImageManager::GetSingleton()->AddImage("item_ironOre",
        "Image/item/ironOre.bmp", 32, 32,
        true, RGB(255, 0, 255));
    
    ImageManager::GetSingleton()->AddImage("item_goldOre",
        "Image/item/goldOre.bmp", 32, 32,
        true, RGB(255, 0, 255));
    
    ImageManager::GetSingleton()->AddImage("item_ironIngot",
        "Image/item/ironIngot.bmp", 32, 32,
        true, RGB(255, 0, 255));
        
    ImageManager::GetSingleton()->AddImage("item_goldIngot",
        "Image/item/goldIngot.bmp", 32, 32,
        true, RGB(255, 0, 255));
        
    ImageManager::GetSingleton()->AddImage("item_coin",
        "Image/item/coin.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("item_brick",
        "Image/item/brick.bmp", 32, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("char_theForager_l",
        "Image/char_theForager_l.bmp", 48, 32, 4, 2,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("char_theForager_r",
        "Image/char_theForager_r.bmp", 48, 32, 4, 2,
        true, RGB(255, 0, 255));
    
    ImageManager::GetSingleton()->AddImage("floor_bridge",
        "Image/floor/bridge.bmp", 16, 16,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_inventorySlot",
        "Image/ui/inventorySlot.bmp", 22, 22,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_inventorySlotSelection",
        "Image/ui/inventorySlotSelection.bmp", 860, 90, 10, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_icon_furnace",
        "Image/ui/iconFurnace.bmp", 31, 42,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_icon_forge",
        "Image/ui/iconForge.bmp", 29, 29,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_icon_bridge",
        "Image/ui/iconBridge.bmp", 34, 32,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_button",
        "Image/ui/button.bmp", 93, 33,
        true, RGB(255, 0, 255));
    
    ImageManager::GetSingleton()->AddImage("ui_buttonSmall",
        "Image/ui/buttonSmall.bmp", 93, 25,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_menuTab3",
        "Image/ui/menuTab3.bmp", 138, 48,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_textBox",
        "Image/ui/textBox.bmp", 220, 400,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_textBoxShort",
        "Image/ui/textBoxShort.bmp", 220, 200,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_arrowSmall",
        "Image/ui/arrowSmall.bmp", 28, 20, 2, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("ui_tabIcons",
        "Image/ui/tabIcons.bmp", 160, 32, 5, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("landSelection1x1",
        "Image/landSelection1x1.bmp", 320, 32, 10, 1,
        true, RGB(255, 0, 255));
    
    ImageManager::GetSingleton()->AddImage("landSelection2x2",
        "Image/landSelection2x2.bmp", 400, 40, 10, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("keyboardE",
        "Image/keyboardE.bmp", 76, 72,
        true, RGB(255, 0, 255));
    
    ImageManager::GetSingleton()->AddImage("progressCircle",
        "Image/progressCircle.bmp", 256, 32, 8, 1,
        true, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("title",
        "Image/Title.bmp", 1190, 790,
        true, RGB(255, 0, 255));

    
    return S_OK;
}

void ImageManager::Release()
{
    // 모든 이미지에 대한 메모리 해제가 이루어 진다.
    map<string, Image*>::iterator it;
    for (it = mImageDatas.begin(); it != mImageDatas.end(); it++)
    {
        if ((it->second))
        {
            (it->second)->Release();
            delete (it->second);
            (it->second) = nullptr;
        }
    }
    mImageDatas.clear();

    ReleaseSingleton();
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    Image* image = nullptr;

    // 맵에 키에 해당하는 데이터가 있으면 추가생성없이 리턴
    image = FindImage(key);
    if (image)
    {
        return image;
    }

    // 없으면 생성 후 맵에 추가
    image = new Image();
    if (FAILED(image->Init(fileName, width, height, isTransparent, transColor)))
    {
        image->Release();
        delete image;

        return nullptr;
    }

    mImageDatas.insert(make_pair(key, image));
    return image;
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    Image* image = nullptr;

    // 맵에 키에 해당하는 데이터가 있으면 추가생성없이 리턴
    image = FindImage(key);
    if (image)
    {
        return image;
    }

    // 없으면 생성 후 맵에 추가
    image = new Image();
    if (FAILED(image->Init(fileName, width, height,
        maxFrameX, maxFrameY, isTransparent, transColor)))
    {
        image->Release();
        delete image;

        return nullptr;
    }

    mImageDatas.insert(make_pair(key, image));
    return image;
}

void ImageManager::DeleteImage(string key)
{
    map<string, Image*>::iterator it;
    it = mImageDatas.find(key);

    if (it == mImageDatas.end())
    {
        return;
    }

    // 맵에 key, value pair가 있는 상태
    // value에 해당하는 Image* 데이터도 메모리 해제해야 한다.
    (it->second)->Release();
    delete (it->second);
    (it->second) = nullptr;

    mImageDatas.erase(it);
}

Image* ImageManager::FindImage(string key)
{
    map<string, Image*>::iterator it;
    it = mImageDatas.find(key);

    if (it == mImageDatas.end())
    {
        return nullptr;
    }

    return it->second;
}
