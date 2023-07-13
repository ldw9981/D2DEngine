#pragma once
#include "Transform.h"
class RenderComponent :
	virtual public Transform
{
public:
	RenderComponent() = default;
	~RenderComponent() = default;

	virtual void Render() = 0;
};

