#pragma once
#include "ClassParent.h"

class ClassChild :public ClassParent
{
public:
	ClassChild()
	{
		std::cout << __FUNCTION__ << "\n";
	}
	~ClassChild()			// virtual �� �����ص� ���� �Լ��� virtual Ư���� �ٴ´�.
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

