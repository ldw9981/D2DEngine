#pragma once
#include "Object.h"

class GameObject;
class Component : public Object
{
public:
	Component() : m_pOwner(nullptr)
	{
	}
	virtual ~Component() = 0;

protected:
	GameObject* m_pOwner;
public:
	virtual void Update(float DeltaTime) = 0;
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
};

