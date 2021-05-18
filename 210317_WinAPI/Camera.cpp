#include "Camera.h"

HRESULT Camera::Init()
{
	pos = FPOINT{ 0, 0 };
	scale = 1;
	screenSize = POINT{ 512, 512 };
	return S_OK;
}
