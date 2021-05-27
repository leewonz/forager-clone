#include "Drop.h"
#include "GameData.h"
#include "Image.h"

HRESULT Drop::Init()
{
	size = FPOINT{ SIZE, SIZE };
	offset = FPOINT{ -SIZE / 2, -SIZE / 2 };
	return S_OK;
}

void Drop::Update()
{
}

void Drop::Release()
{
}

void Drop::Render(HDC hdc)
{
	GameData* gameData = GameData::GetSingleton();
	Image* img = gameData->GetItemInfo(item.idx)->img;
	//Image::StageRectangle(hdc, GetBox());
	img->StageRender(hdc, pos.x, pos.y, 0, 0, true, 0.5);
}
