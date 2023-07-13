#pragma once
#include "RenderComponent.h"

class AnimationRender: public RenderComponent
{
public:
	AnimationRender()
	{
		
	}
	~AnimationRender() 
	{
	}


	virtual void Render();
	virtual void Update();
};

