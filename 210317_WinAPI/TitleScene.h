#pragma once
#include "GameNode.h"
class TitleScene :
    public GameNode
{
private:
    const float BUTTON_SIZE = 2.0f;
    Image* bgImg;
    Image* titleImg;
    Image* buttonImg;
    RECT gameButtonRect;
    RECT mapToolButtonRect;

public:
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render(HDC hdc);
};

