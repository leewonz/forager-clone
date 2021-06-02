#pragma once
#include "config.h"
#include "GameData.h"

class GameNode;
class Drop;
class DropContainer
{
private:
	GameNode* scene;
	vector<Drop*> drops;
	multimap<float, Drop*> mDrops;
	multimap<float, Drop*>::iterator iterMDrops;
public:

	// Sort�ϴ� ��
	// vector<Drop*>, map<float, Drop*> ����
	// ���� �ڵ����� �������� ���ĵȴ�.
	// ���� ��ο��ϴ� �뵵�θ� ����Ѵ�.
	// map�� iterator�̿��ؼ� sort�� ������� ���

	HRESULT Init(GameNode* scene);
	void Update();
	void Release();
	void Render(HDC hdc);

	inline GameNode* GetScene() { return scene; };
	inline void SetScene(GameNode* scene) { this->scene = scene; };
	inline int GetSize() { return drops.size(); };
	inline Drop* GetDrop(int idx) { return drops[idx]; };
	pair<float, Drop*> Begin();
	pair<float, Drop*> Next();
	pair<float, Drop*> Peek();
	bool isEnded();
	multimap<float, Drop*>::iterator getMapBegin() { return mDrops.begin(); }
	multimap<float, Drop*>::iterator getMapEnd() { return mDrops.end(); }
	void AddDrop(Item item, FPOINT pos);
	void RemoveDrop(int idx);
};

