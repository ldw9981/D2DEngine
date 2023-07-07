#pragma once
#include "Deligate.h"

class Deligate;
class MyComponent4 {
public:

	std::wstring m_Text = L"MyClass1";
public:
	void CallbackFunction(int value) {
		std::cout << "Callback called with value: " << this << " " << value << std::endl;
	}
};