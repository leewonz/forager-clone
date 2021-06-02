#include "Drop.h"
#include "GameData.h"
#include "Image.h"
#include "TimerManager.h"

HRESULT Drop::Init()
{
	size = FPOINT{ SIZE, SIZE };
	offset = FPOINT{ -SIZE / 2, -SIZE / 2 };
	initTime = TimerManager::GetSingleton()->GetProgramTime();
	animProgress = 0.0f;
	return S_OK;
}

void Drop::Update()
{
	GameData* gameData = GameData::GetSingleton();
	Image* img = gameData->GetItemInfo(item.idx)->img;

	if (animProgress < 1.0f)
	{
		animProgress = min(
			1.0f,
			animProgress + TimerManager::GetSingleton()->GetElapsedTime() * ANIM_SPEED);
	}
}

void Drop::Release()
{
}

void Drop::Render(HDC hdc)
{
	GameData* gameData = GameData::GetSingleton();
	Image* img = gameData->GetItemInfo(item.idx)->img;
	float time = TimerManager::GetSingleton()->GetProgramTime();
	float yMovement = (sin((time - initTime) * 180.0f * 3.14f / 180.0f) * 1.0f);
	//Image::StageRectangle(hdc, GetBox());
	float yJump = 4.0f * ANIM_JUMP_HEIGHT * (animProgress - 1.0f) * (animProgress);
	FPOINT finalPos = FPOINT{
		(1.0f - animProgress) * animStartPos.x + (animProgress) * pos.x,
		(1.0f - animProgress) * animStartPos.y + (animProgress) * pos.y + yMovement + yJump
	};
	img->StageRender(hdc, finalPos.x, finalPos.y, 0, 0, true, 0.5f);
	Image::StageRectangle(hdc, RECT{ (LONG)pos.x, (LONG)pos.y, (LONG)pos.x + 1, (LONG)pos.y + 1 });
}

void Drop::SetAnimationStartPos(FPOINT animStartPos)
{
	this->animStartPos = animStartPos;
	animProgress = 0.0f;
}
