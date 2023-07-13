#pragma once
#include "Transform.h"


class AnimRenderer: virtual public Transform
{
public:
	AnimRenderer()
	{
		
	}
	~AnimRenderer() 
	{
	}


	virtual void Render();
	virtual void Update();
};

