#pragma once
#include "config.h"
#include "GameData.h"

class Drop;
class DropContainer
{
private:
	vector<Drop*> drops;
public:
	HRESULT Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	inline int GetSize() { return drops.size(); }
	inline Drop* GetDrop(int idx) { return drops[idx]; };
	void AddDrop(Item item, FPOINT pos);
	void RemoveDrop(int idx);
};

