#pragma once
#include "AnimRenderer.h"
#include "Transform.h"
#include <iostream>

class BoxRenderer :
    virtual public Transform
{
public:
	BoxRenderer()
	{
		
	}
	~BoxRenderer()
	{

	}
	
	virtual void Update() override
	{
		std::cout << "BoxRenderer Update" << std::endl;
	}
};

