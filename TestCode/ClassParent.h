#pragma once

class ClassParent
{
public:
	ClassParent()
	{
		std::cout << __FUNCTION__ << "\n";
	}
	virtual ~ClassParent()
	{
		std::cout << __FUNCTION__ << "\n";
	}

	virtual void Function()			// virtual 키워드는 자식 클래스에서도 유지된다.
	{
		std::cout << __FUNCTION__ << "\n";
	}
public:
	int ParentData;

};

