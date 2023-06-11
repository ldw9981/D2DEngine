#pragma once
class TestClass
{
public:
	TestClass()
	{

	}
	virtual ~TestClass()
	{
		OutputDebugString(L"TestClass::~TestClass()\n");
	}

};

