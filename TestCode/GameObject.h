#pragma once
#include "Transform.h"
#include "AnimRenderer.h"
#include "Transform.h"
#include "BoxRenderer.h"
#include "Movement.h"

class GameObject: public AnimRenderer, public Movement
{
public:
	GameObject() {}
	~GameObject() {}

	virtual void Print()
	{
		int a;
	}


	virtual void Update() override
	{
		AnimRenderer::Update();
		Movement::Update();
	}
};

