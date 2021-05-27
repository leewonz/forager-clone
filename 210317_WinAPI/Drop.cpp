#include "Drop.h"
#include "GameData.h"
#include "Image.h"
#include "TimerManager.h"

HRESULT Drop::Init()
{
	size = FPOINT{ SIZE, SIZE };
	offset = FPOINT{ -SIZE / 2, -SIZE / 2 };
	initTime = TimerManager::GetSingleton()->GetProgramTime();
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
	float time = TimerManager::GetSingleton()->GetProgramTime();
	float yMovement = (sin((time - initTime) * 180.0f * 3.14f / 180.0f) * 2.0f);
	//Image::StageRectangle(hdc, GetBox());
	img->StageRender(hdc, pos.x, pos.y + yMovement, 0, 0, true, 0.5f);
}
