#include "Image.h"

Camera* Image::cam = nullptr;
CameraStatus Image::camStatus = CameraStatus();

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = 
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = FALSE;
    this->transColor = FALSE;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height,
    bool isTransparent/* = FALSE*/, COLORREF transColor/* = FALSE*/)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = 
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    // 알파 블랜드
    imageInfo->hBlendDC = CreateCompatibleDC(hdc);
    imageInfo->hBlendBit = CreateCompatibleBitmap(hdc, 
        imageInfo->width, imageInfo->height);
    imageInfo->hOldBlendBit = (HBITMAP)SelectObject(imageInfo->hBlendDC, 
        imageInfo->hBlendBit);

    imageInfo->maxFrameX = 1;
    imageInfo->maxFrameY = 1;
    imageInfo->frameWidth = width;
    imageInfo->frameHeight = height;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap =
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        // bitmap 에 있는 이미지 정보를 다른 비트맵에 복사
        BitBlt(
            hdc,                // 복사 목적지 DC
            x, y,               // 복사 시작 위치
            imageInfo->width,   // 원본에서 복사될 가로크기
            imageInfo->height,  // 원본에서 복사될 세로크기
            imageInfo->hMemDC,  // 원본 DC
            0, 0,               // 원본에서 복사 시작 위치
            SRCCOPY             // 복사 옵션
        );     
    }
}

void Image::Render(HDC hdc, int destX, int destY, float scale, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (scale * imageInfo->width / 2);
        y = destY - (scale * imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width * scale, imageInfo->height * scale,
            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        StretchBlt(hdc,
            x, x,
            imageInfo->width * scale,
            imageInfo->height * scale,
            imageInfo->hMemDC,
            0, 0, 
            imageInfo->width,
            imageInfo->width,
            SRCCOPY);
    }
}

void Image::Render(HDC hdc, RECT src, RECT dest)
{

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,
            dest.left, dest.top,
            dest.right - dest.left, dest.bottom - dest.top,

            imageInfo->hMemDC,
            src.left, src.top,
            src.right - src.left, src.bottom - src.top,
            transColor
        );
    }
    else
    {
        StretchBlt(hdc,
            dest.left, dest.top,
            dest.right - dest.left,
            dest.bottom - dest.top,
            imageInfo->hMemDC,
            src.left, src.top,
            src.right - src.left,
            src.bottom - src.top,
            SRCCOPY);
    }
}

void Image::FrameRender(HDC hdc, int destX, int destY,
    int currFrameX, int currFrameY, bool isCenterRenderring, float size)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX;
    int y = destY;

    if (isCenterRenderring)
    {
        POINT offset = OffsetFromCenter(size);
        x += offset.x;
        y += offset.y;
    }

    RECT src = { imageInfo->frameWidth * imageInfo->currFrameX,
                 imageInfo->frameHeight * imageInfo->currFrameY,
                 imageInfo->frameWidth * (imageInfo->currFrameX + 1),
                 imageInfo->frameHeight * (imageInfo->currFrameY + 1), };

    RECT dest = { x,
                  y,
                  x + (int)(imageInfo->frameWidth * size),
                  y + (int)(imageInfo->frameHeight * size) };
    
    Render(hdc, src, dest);
}

void Image::FrameRender(HDC hdc, RECT dest, int currFrameX, int currFrameY)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    RECT src = { imageInfo->frameWidth * imageInfo->currFrameX,
                 imageInfo->frameHeight * imageInfo->currFrameY,
                 imageInfo->frameWidth * (imageInfo->currFrameX + 1),
                 imageInfo->frameHeight * (imageInfo->currFrameY + 1), };

    Render(hdc, src, dest);
}

void Image::AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    // 1. 목적지 DC(hdc)에 그려져 있는 내용을 BlendDC에 복사
    BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
        hdc, x, y, SRCCOPY);

    //GdiTransparentBlt(imageInfo->)

    // 2. 출력할 이미지 DC에 내용을 BlendDC에 지정한 색상을 제외하면서 복사


    // 3.
    AlphaBlend(hdc, x, y, imageInfo->width, imageInfo->height,
        imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
}

void Image::StageRender(HDC hdc, float destX, float destY, int currFrameX, int currFrameY, bool isCenterRendering, float size)
{
    static RECT intersection = RECT{ 0, 0, 0, 0 };
    if (cam)
    {
        FPOINT camPos = cam->WorldToCamera(FPOINT{ destX, destY });
        float camScale = camStatus.scale;
        POINT camSize = camStatus.screenSize;
        if (isCenterRendering)
        {
            POINT offset = OffsetFromCenter(size * camScale);
            camPos.x += offset.x;
            camPos.y += offset.y;
        }
        RECT destRect = RECT{ (LONG)camPos.x,
                              (LONG)camPos.y,
                              (LONG)(camPos.x + (imageInfo->frameWidth * size * camScale)),
                              (LONG)(camPos.y + (imageInfo->frameHeight * size * camScale)) };
        RECT screenRect = RECT{ 0,0, camSize.x, camSize.y };
        if (!IntersectRect(&intersection, &screenRect, &destRect)) { return; }
        //FrameRender(hdc, camPos.x, camPos.y, currFrameX, currFrameY, isCenterRendering, size * camScale);
        FrameRender(hdc, destRect, currFrameX, currFrameY);
    }
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        if (imageInfo->hBlendDC != NULL)
        {
            SelectObject(imageInfo->hBlendDC, imageInfo->hOldBlendBit);
            DeleteObject(imageInfo->hBlendBit);
            DeleteDC(imageInfo->hBlendDC);
        }

        delete imageInfo;
        imageInfo = nullptr;
    }
}

void Image::StageRectangle(HDC hdc, RECT rect)
{
    int debug = DEBUG_DRAW;
    if(debug)
    { 
        RECT worldRect = Camera::GetSingleton()->WorldToCamera(rect);
        Rectangle(hdc, worldRect.left, worldRect.top, worldRect.right, worldRect.bottom);
    }
}
