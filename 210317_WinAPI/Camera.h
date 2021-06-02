#pragma once
#include "Singleton.h"
#include "config.h"

// 카메라 위치, 스케일 정하기
// 절대죄표 - 상대좌표 변환

struct CameraStatus
{
	FPOINT pos;
	float scale;
	POINT screenSize;
};

class Camera : public Singleton<Camera>
{
private:
	CameraStatus status;
public:
	inline FPOINT GetPos() { return status.pos; }
	inline void SetPos(FPOINT pos) { this->status.pos = pos; }
	inline float GetScale() { return status.scale; }
	inline void SetScale(float scale) { this->status.scale = scale; }
	inline POINT GetScreenSize() { return status.screenSize; }
	inline void SetScreenSize(POINT screenSize) { this->status.screenSize = screenSize; }

	HRESULT Init(); 
	virtual HRESULT InitSingleton();

	inline FPOINT GetPosCenter() 
	{
		return FPOINT{ (status.pos.x) + (status.scale * (float)status.screenSize.x * 0.5f),
					   (status.pos.y) + (status.scale * (float)status.screenSize.y * 0.5f) };
	}

	inline void SetPosCenter(FPOINT pos) 
	{
		this->status.pos = FPOINT{ (pos.x) - ( (float)status.screenSize.x * 0.5f / status.scale),
					        (pos.y) - ( (float)status.screenSize.y * 0.5f / status.scale) };
	}

	inline FPOINT WorldToCamera(FPOINT worldSpacePos) 
	{
		return FPOINT{ (worldSpacePos.x - status.pos.x) * status.scale,
					   (worldSpacePos.y - status.pos.y) * status.scale };
	}

	inline FPOINT CameraToWorld(FPOINT cameraSpacePos)
	{
		return FPOINT{ (cameraSpacePos.x / status.scale) + status.pos.x,
					   (cameraSpacePos.y / status.scale) + status.pos.y };
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

	inline CameraStatus GetStatus() { return status; }
	inline void SetStatus() { this->status = status; }
};

