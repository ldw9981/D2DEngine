#pragma once

#include "Component.h"

class Transform : Component
{
public:
	Transform()
	:m_RelativePositionX(0)
	{
	}
	virtual ~Transform() {}

public:
	int m_RelativePositionX;
	int m_RelativeTransform;
	int m_WorldTransform;
	Transform* m_pParent;
public:
	const int& GetWorldTransform()
	{
		return m_WorldTransform;
	}
	virtual void Update();
};

