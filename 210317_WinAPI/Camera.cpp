#include "Camera.h"

HRESULT Camera::InitSingleton()
{
	Init();
	return S_OK;
}

HRESULT Camera::Init()
{
	status.pos = FPOINT{ 0, 0 };
	status.scale = 1;
	status.screenSize = POINT{ 512, 512 };
	return S_OK;
}
