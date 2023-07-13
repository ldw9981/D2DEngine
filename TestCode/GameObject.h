#pragma once
#include "Transform.h"
#include "AnimationRender.h"
#include "Transform.h"
#include "BoxRender.h"
#include "Movement.h"

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}

	virtual void Render()=0;;
	virtual void Update()=0;
};

