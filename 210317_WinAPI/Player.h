#pragma once
#include "StageObject.h"
class Image;
class Player :
    public StageObject
{
private:
	const int BOX_SIZE_X = 10;
	const int BOX_SIZE_Y = 10;
	const int IMG_OFFSET_X = 0;
	const int IMG_OFFSET_Y = -4;

	const float MOVE_SPEED = 120.0f;
	const float MAX_FRAME_TIME = 0.1f;

	Image* img_l;
	Image* img_r;
	int frameX;
	int frameY;
	float frameTime;
public:
	virtual HRESULT Init();		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	void Move(FPOINT dir);
};

