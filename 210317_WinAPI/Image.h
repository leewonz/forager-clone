#pragma once
#include "config.h"
#include "Camera.h"

class Camera;
class Image
{
private:
	static Camera* cam;
	static CameraStatus camStatus;
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// ������Ʈ ��ü�� ���� ��ų �̹���
		FILE,			// �ܺο��� �ε��� �̹���
		EMPTY,			// ��ü ���� �̹���
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ������ ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int width;			// �̹��� ���� ũ��
		int height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

		// ���ĺ���
		HDC hBlendDC;
		HBITMAP hBlendBit;
		HBITMAP hOldBlendBit;

		// �ִϸ��̼� ���� (�����ӵ�����)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			hBlendDC = NULL;
			hBlendBit = NULL;
			hOldBlendBit = NULL;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;		// �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

	BLENDFUNCTION blendFunc;

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false);
	void Render(HDC hdc, int destX, int destY,
		float scale, bool isCenterRenderring = false);
	void Render(HDC hdc, RECT src, RECT dest);
	void FrameRender(HDC hdc, int destX, int destY,
		int currFrameX, int currFrameY, bool isCenterRenderring = false, float size = 1);
	void FrameRender(HDC hdc, RECT dest, int currFrameX, int currFrameY);
	void AlphaRender(HDC hdc, int destX, int destY,
		bool isCenterRenderring = false);
	void StageRender(HDC hdc, float destX, float destY,
		int currFrameX, int currFrameY, bool isCenterRenderring = false, float size = 1);

	void Release();

	// get, set
	HDC GetMemDC()
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}

	BLENDFUNCTION* GetBlendFunc() { return &(this->blendFunc); }

	int GetWidth() { return this->imageInfo->width; }
	int GetHeight() { return this->imageInfo->height; }
	int GetFrameWidth() { return this->imageInfo->frameWidth; }
	int GetFrameHeight() { return this->imageInfo->frameHeight; }

	IMAGE_INFO* const  GetImageInfo() { return this->imageInfo; }

	inline POINT OffsetFromCenter(float scale)
	{
		return POINT{
		-(int)(imageInfo->frameWidth * scale / 2),
		-(int)(imageInfo->frameHeight * scale / 2) };
	}

	static void StageRectangle(HDC hdc, RECT rect);
	static void SetCamera(Camera* cam) { Image::cam = cam; }
	static void SetCameraStatus(Camera* cam) { Image::camStatus = cam->GetStatus(); }
};

