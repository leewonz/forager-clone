#include "Player.h"
#include "Image.h"
#include "ImageManager.h"

HRESULT Player::Init()
{
    img = ImageManager::GetSingleton()->FindImage("char_theForager");

    return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
    frameTime += TimerManager::GetSingleton()->GetElapsedTime();
    if (frameTime > 0.1)
    {
        ++frameX;
        frameX %= (frameY == 0) ? 3 : 4;
        frameTime -= 0.1;
    }
}

void Player::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x, pos.y, frameX, frameY, true);
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

        float angle = atan2(dir.y, dir.x);

        pos.x += cosf(angle) * MOVE_SPEED * 
            TimerManager::GetSingleton()->GetElapsedTime();
        pos.y += sinf(angle) * MOVE_SPEED * 
            TimerManager::GetSingleton()->GetElapsedTime();
    }
}
