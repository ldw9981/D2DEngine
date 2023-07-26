#pragma once
#include "Transform.h"
#include <iostream>

class Movement: virtual public Transform
{
public:
	Movement()= default;
	~Movement() = default;

	virtual void Update(float DeltaTime) override
	{
		std::cout << "Movement Update" << std::endl;
	}
};

