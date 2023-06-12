#pragma once

#include "ClassParent.h"
#include "ClassChild.h"

class ClassOwner
{
public:
	ClassOwner()
	{
		std::cout << __FUNCTION__ << "\n";
		A = new ClassChild;
	}
	~ClassOwner()
	{
		delete A;
		std::cout << __FUNCTION__ << "\n";

	}

	ClassChild* A;
};

