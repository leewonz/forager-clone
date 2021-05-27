#pragma once
#include "config.h"
#include "GameData.h"

class Drop;
class DropContainer
{
private:
	vector<Drop*> drops;
public:

	// Sort하는 법
	// vector<Drop*>, map<float, Drop*> 생성
	// 맵은 자동으로 오름차순 정렬된다.
	// 맵은 드로우하는 용도로만 사용한다.
	// map의 iterator이용해서 sort된 순서대로 출력

	HRESULT Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	inline int GetSize() { return drops.size(); }
	inline Drop* GetDrop(int idx) { return drops[idx]; };
	void AddDrop(Item item, FPOINT pos);
	void RemoveDrop(int idx);
};

