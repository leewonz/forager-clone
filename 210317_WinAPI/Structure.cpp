#include "Structure.h"
#include "StructureInfo.h"
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
	RECT box = GetBox();
	Rectangle(hdc, box.left, box.top, box.right, box.bottom);
	GetStage()->GetStructureInfo(type)->GetImg()->
		Render(hdc, box.left, box.top, false);
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
