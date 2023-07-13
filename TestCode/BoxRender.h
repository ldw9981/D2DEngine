#pragma once
#include "RenderComponent.h"
#include "Transform.h"
#include <iostream>

class BoxRender :
public RenderComponent
{
public:
	BoxRender()
	{
		
	}
	~BoxRender()
	{

	}
	
	virtual void Render()
	{
		std::cout << "BoxRenderer Render" << std::endl;
	}

	virtual void Update() override
	{
		std::cout << "BoxRenderer Update WorldTrasnform" << m_WorldTransform <<  std::endl;
	}
};

