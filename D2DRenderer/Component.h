#pragma once
#include "Object.h"
/*
	게임 오브젝트의 기능을 컴포넌트 단위로 분리하기 위한 추상 클래스
	게임오브젝트는 컴포넌트의 조합으로 이루어진다.
	컴포넌트의 생성은 GameObject의 CreateComponent<T> 를 통해 이루어진다.

	지금당장은 Object의 역할이 없으므로 Object를 상속받지 않는다.
*/
class GameObject;
class Component 
{
public:
	Component() : m_pOwner(nullptr)
	{
	}
	virtual ~Component() {};

protected:
	GameObject* m_pOwner;
public:
	virtual void Update() = 0;
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
};

