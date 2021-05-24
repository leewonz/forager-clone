#include "DropContainer.h"
#include "Drop.h"

HRESULT DropContainer::Init()
{
	
	return S_OK;
}

void DropContainer::Update()
{
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
    for (int i = 0; i < drops.size(); i++)
    {
        drops[i]->Render(hdc);
    }
}

void DropContainer::AddDrop(Item item, FPOINT pos)
{
    Drop* drop = new Drop();
    drop->Init();
    drop->SetPos(pos);
    drop->SetItem(item);
    drops.push_back(drop);
}

void DropContainer::RemoveDrop(int idx)
{
    drops.erase(drops.begin() + idx);
}
