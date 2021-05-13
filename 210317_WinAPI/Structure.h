#pragma once

#include "StageObject.h"

class Stage;
class Structure : public StageObject
{
	Stage* parentStage;
	int type;

public:
	virtual HRESULT Init(Stage* parentStage);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetStage(Stage* parentStage);
	Stage* GetStage();
	void SetStructureType(int type);
	int GetStructureType();
};

