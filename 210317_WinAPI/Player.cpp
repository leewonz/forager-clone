#include "Player.h"
#include "Image.h"
#include "ImageManager.h"
#include "Camera.h"

HRESULT Player::Init()
{
    img = ImageManager::GetSingleton()->FindImage("char_theForager");
    SetPos(FPOINT{ 100, 100 });
    SetOffset(FPOINT{ (float)-BOX_SIZE_X / 2, (float)-BOX_SIZE_Y / 2 });
    SetSize(FPOINT{ (float)BOX_SIZE_X, (float)BOX_SIZE_Y });
    return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
    frameTime += TimerManager::GetSingleton()->GetElapsedTime();
    if (frameTime > MAX_FRAME_TIME)
    {
        ++frameX;
        frameX %= (frameY == 0) ? 3 : 4;
        frameTime -= MAX_FRAME_TIME;
    }
}

void Player::Render(HDC hdc)
{
    FPOINT camPos = Camera::GetSingleton()->WorldToCamera(pos);
    //img->FrameRender(hdc, camPos.x, camPos.y, frameX, frameY, true);
    img->StageRender(hdc, pos.x, pos.y, frameX, frameY, true);
    //Rectangle(hdc, pos.x, pos.y, pos.x + 100, pos.y + 100);
}

void Player::Move(FPOINT dir)
{
    if (abs(dir.x) < 0.01f && abs(dir.y) < 0.01f)
    {
        if (frameY == 1)
        {
            frameY = 0;
            frameX = 0;
        }
        return;
    }
    else
    {
        if (frameY == 0)
        {
            frameY = 1;
            frameX = 0;
        }

        float angle = (float)atan2(dir.y, dir.x);

        pos.x += cosf(angle) * MOVE_SPEED * 
            TimerManager::GetSingleton()->GetElapsedTime();
        pos.y += sinf(angle) * MOVE_SPEED * 
            TimerManager::GetSingleton()->GetElapsedTime();
    }
}
