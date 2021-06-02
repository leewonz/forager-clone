#include "DropContainer.h"
#include "Drop.h"

HRESULT DropContainer::Init(GameNode* scene)
{
    SetScene(scene);
	return S_OK;
}

void DropContainer::Update()
{
    for (int i = 0; i < drops.size(); i++)
    {
        drops[i]->Update();
    }
}

void DropContainer::Release()
{
    for (int i = 0; i < drops.size(); i++)
    {
        SAFE_RELEASE(drops[i]);
    }
}

void DropContainer::Render(HDC hdc)
{
    //for (int i = 0; i < drops.size(); i++)
    //{
    //    drops[i]->Render(hdc);
    //}
    multimap<float, Drop*>::iterator iter;
    for (iter = mDrops.begin(); iter != mDrops.end(); iter++)
    {
        iter->second->Render(hdc);
    }
}

pair<float, Drop*> DropContainer::Begin()
{
    iterMDrops = mDrops.begin();
    return Peek();
}

pair<float, Drop*> DropContainer::Next()
{
    iterMDrops++;
    return Peek();
}

pair<float, Drop*> DropContainer::Peek()
{
    if (!isEnded())
    {
        return pair<float, Drop*>{ iterMDrops->first, iterMDrops->second };
    }
    else
    {
        return pair<float, Drop*>{ -1.0f, nullptr };
    }
}

bool DropContainer::isEnded()
{
    return iterMDrops == mDrops.end();
}

void DropContainer::AddDrop(Item item, FPOINT pos)
{
    Drop* drop = new Drop();
    FPOINT RandomItemPos = FPOINT{
        pos.x + (float)((rand() % 15) - 7),
        pos.y + (float)((rand() % 15) - 7),
    };

    drop->Init();
    drop->SetItem(item);
    drop->SetScene(scene);
    drop->SetAnimationStartPos(pos);
    drop->SetPos(RandomItemPos);
    drops.push_back(drop);
    mDrops.insert({ pos.y, drop });
}

void DropContainer::RemoveDrop(int idx)
{
    vector<Drop*>::iterator vIter;
    multimap<float, Drop*>::iterator mapIter;

    vIter = drops.begin() + idx;
    Drop* willErase = *vIter;
    drops.erase(vIter);

    for (mapIter = mDrops.begin(); mapIter != mDrops.end(); mapIter++)
    {
        if (mapIter->second == willErase)
        {
            mDrops.erase(mapIter);
            break;
        }
    }
    SAFE_RELEASE(willErase);
}
