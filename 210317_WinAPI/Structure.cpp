#include "Structure.h"
#include "StructureInfo.h"
#include "GameData.h"
#include "Stage.h"
#include "Image.h"

HRESULT Structure::Init(Stage* parentStage)
{
	SetStage(parentStage);
	return S_OK;
}

void Structure::Release()
{
}

void Structure::Update()
{
}

void Structure::Render(HDC hdc)
{
	StructureInfo* info = GameData::GetSingleton()->GetStructureInfo(type);
	RECT box = GetBox();
	POINT imgOffset = info->GetImgOffset();

	Image::StageRectangle(hdc, box);
	info->GetImg()->
		StageRender(hdc, box.left + imgOffset.x, box.top + imgOffset.y, 0, 0, false, 1);
}

void Structure::SetStage(Stage* parentStage)
{
	this->parentStage = parentStage;
}

Stage* Structure::GetStage()
{
	return parentStage;
}

void Structure::SetStructureType(int type)
{
	this->type = type;
}

int Structure::GetStructureType()
{
	return type;
}
