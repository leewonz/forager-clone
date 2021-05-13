#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
    ImageManager::GetSingleton()->AddImage("sampleTile",
        "Image/sampleTile.bmp", 100, 40, 5, 2,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_grass",
        "Image/tile_grass.bmp", 100, 80, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_desert",
        "Image/tile_desert.bmp", 100, 80, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_winter",
        "Image/tile_winter.bmp", 100, 80, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_fire",
        "Image/tile_fire.bmp", 100, 80, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("tile_graveyard",
        "Image/tile_graveyard.bmp", 100, 80, 5, 4,
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("sampleBuilding",
        "Image/sampleBuilding.bmp", 30, 42, 
        false, RGB(255, 0, 255));

    ImageManager::GetSingleton()->AddImage("char_theForager",
        "Image/char_theForager.bmp", 48, 32, 4, 2,
        false, RGB(255, 0, 255));
    

    return S_OK;
}

void ImageManager::Release()
{
    // ��� �̹����� ���� �޸� ������ �̷�� ����.
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

    // �ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ �߰��������� ����
    image = FindImage(key);
    if (image)
    {
        return image;
    }

    // ������ ���� �� �ʿ� �߰�
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

    // �ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ �߰��������� ����
    image = FindImage(key);
    if (image)
    {
        return image;
    }

    // ������ ���� �� �ʿ� �߰�
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

    // �ʿ� key, value pair�� �ִ� ����
    // value�� �ش��ϴ� Image* �����͵� �޸� �����ؾ� �Ѵ�.
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
