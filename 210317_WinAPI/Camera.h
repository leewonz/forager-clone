#pragma once
#include "Singleton.h"
#include "config.h"

// 카메라 위치, 스케일 정하기
// 절대죄표 - 상대좌표 변환
class Camera : public Singleton<Camera>
{
private:
	FPOINT pos;
	float scale;
	POINT screenSize;
public:
	inline FPOINT GetPos() { return pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline float GetScale() { return scale; }
	inline void SetScale(float scale) { this->scale = scale; }
	inline POINT GetScreenSize() { return screenSize; }
	inline void SetScreenSize(POINT screenSize) { this->screenSize = screenSize; }

	HRESULT Init(); 
	virtual HRESULT InitSingleton();

	inline FPOINT GetPosCenter() 
	{
		return FPOINT{ (pos.x) + (scale * (float)screenSize.x * 0.5f),
					   (pos.y) + (scale * (float)screenSize.y * 0.5f) };
	}

	inline void SetPosCenter(FPOINT pos) 
	{
		this->pos = FPOINT{ (pos.x) - ( (float)screenSize.x * 0.5f / scale),
					        (pos.y) - ( (float)screenSize.y * 0.5f / scale) };
	}

	inline FPOINT WorldToCamera(FPOINT worldSpacePos) 
	{
		return FPOINT{ (worldSpacePos.x - pos.x) * scale,
					   (worldSpacePos.y - pos.y) * scale };
	}

	inline FPOINT CameraToWorld(FPOINT cameraSpacePos)
	{
		return FPOINT{ (cameraSpacePos.x / scale) + pos.x,
					   (cameraSpacePos.y / scale) + pos.y };
	}

	inline RECT WorldToCamera(RECT worldSpaceRect)
	{
		FPOINT start = WorldToCamera(FPOINT{ (float)worldSpaceRect.left, (float)worldSpaceRect.top });
		FPOINT end   = WorldToCamera(FPOINT{ (float)worldSpaceRect.right, (float)worldSpaceRect.bottom });
		return RECT{ (LONG)start.x, (LONG)start.y , (LONG)end.x, (LONG)end.y };
	}

	inline RECT CameraToWorld(RECT cameraSpaceRect)
	{
		FPOINT start = CameraToWorld(FPOINT{ (float)cameraSpaceRect.left, (float)cameraSpaceRect.top });
		FPOINT end   = CameraToWorld(FPOINT{ (float)cameraSpaceRect.right, (float)cameraSpaceRect.bottom });
		return RECT{ (LONG)start.x, (LONG)start.y , (LONG)end.x, (LONG)end.y };
	}
};

