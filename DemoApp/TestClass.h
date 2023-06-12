#pragma once



class TestClass0
{
public:
	TestClass0()
	{
		std::wstring str(__FUNCTIONW__);
		str += L"\n";
		OutputDebugString(str.c_str());
	}
	virtual ~TestClass0()
	{
		std::wstring str(__FUNCTIONW__);
		str += L"\n";
		OutputDebugString(str.c_str());
	}

};

class TestClass1
{
public:
	TestClass1()
	{
		std::wstring str(__FUNCTIONW__);
		str+=L"\n";
		OutputDebugString(str.c_str());
	}
	virtual ~TestClass1()
	{
		std::wstring str(__FUNCTIONW__);
		str += L"\n";
		OutputDebugString(str.c_str());
	}

};

class TestClass2
{
public:
	TestClass2()
	{
		std::wstring str(__FUNCTIONW__);
		str += L"\n";
		OutputDebugString(str.c_str());
	}
	virtual ~TestClass2()
	{
		std::wstring str(__FUNCTIONW__);
		str += L"\n";
		OutputDebugString(str.c_str());
	}

};

