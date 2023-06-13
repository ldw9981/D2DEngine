#pragma once
#include "ClassParent.h"

class ClassChild :public ClassParent
{
public:
	ClassChild()
	{
		std::cout << __FUNCTION__ << "\n";
	}
	~ClassChild()			// virtual 을 제거해도 같은 함수는 virtual 특성은 붙는다.
	{
		std::cout << __FUNCTION__ << "\n";
	}
	void Function()
	{
		std::cout << __FUNCTION__ << "\n";
	}
public:
	int ChildData;
};

