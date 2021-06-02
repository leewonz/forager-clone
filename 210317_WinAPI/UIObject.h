#pragma once
#include "GameNode.h"
class Scene;

enum class UI_MESSAGE
{
	NONE,
	BLOCKED,
	OK,
	BACK,
	END
};

class UIObject : public GameNode
{
protected:
	FPOINT pos;
	FPOINT size;
	bool isActive;
	UIObject* parent;
	Scene* scene;

public:
	UIObject();
	UIObject(UIObject* parentUI);

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return pos; }
	FPOINT GetRelativePos();
	inline void SetSize(FPOINT size) { this->size = size; }
	inline FPOINT GetSize() { return size; }
	inline void SetActive(bool isActive) { 
		if (isActive != this->isActive)
		{
			if (isActive) { OnActivate(); }
			else { OnDeactivate(); }
			this->isActive = isActive;
		}
	}
	inline bool GetActive() { return isActive; }
	inline void SetParent(UIObject* parent) { this->parent = parent; }
	inline UIObject* GetParent() { return parent; }
	inline void SetScene(Scene* scene) { this->scene = scene; }
	inline Scene* GetScene() { return scene; }

	// 선택된 리프 노드의 메시지 반환. 선택된 게 없으면 {NONE, 0} 반환.
	virtual pair<UI_MESSAGE, int> MouseDown(POINT mousePos) = 0;
	// 선택된 리프 노드의 메시지 반환. 선택된 게 없으면 {NONE, 0} 반환.
	virtual pair<UI_MESSAGE, int> MouseUp(POINT mousePos) = 0;
	// 선택된 리프 노드의 메시지 반환. 선택된 게 없으면 {NONE, 0} 반환.
	virtual pair<UI_MESSAGE, int> Back() = 0;
	// SetActive로 자신이 켜졌을 때 호출
	virtual void OnActivate() = 0;
	// SetActive로 자신이 꺼졌을 때 호출
	virtual void OnDeactivate() = 0;

	inline static bool GetIsClicked(pair<UI_MESSAGE, int> msg) 
	{
		return msg.first != UI_MESSAGE::NONE;
	}

	RECT GetBox();
};

