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

	virtual void Function()			// virtual Ű����� �ڽ� Ŭ���������� �����ȴ�.
	{
		std::cout << __FUNCTION__ << "\n";
	}
public:
	int ParentData;

};

