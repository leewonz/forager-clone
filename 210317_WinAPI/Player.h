#pragma once
#include "StageObject.h"
class Image;
class Player :
    public StageObject
{
private:
	const int BOX_SIZE_X = 16;
	const int BOX_SIZE_Y = 16;

	const float MOVE_SPEED = 100.0f;
	const float MAX_FRAME_TIME = 0.1f;

	Image* img;
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

