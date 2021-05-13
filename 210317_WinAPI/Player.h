#pragma once
#include "StageObject.h"
class Image;
class Player :
    public StageObject
{
private:
	const int BOX_SIZE_X = 20;
	const int BOX_SIZE_Y = 20;
	const float MOVE_SPEED = 100.0f;
	Image* img;
	int frameX;
	int frameY;
public:
	virtual HRESULT Init();		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	void Move(FPOINT dir);
};

