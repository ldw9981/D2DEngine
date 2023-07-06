/*

#include <iostream>
#include <vector>
#include <functional>

// Delegate class
class Delegate {
public:
	typedef std::function<int(int, int)> DelegateFunc;  // Define delegate function type

	void AddDelegate(DelegateFunc delegate) {
		delegates_.push_back(delegate);
	}

	int InvokeDelegates(int arg1, int arg2) {
		int result = 0;
		for (const auto& delegate : delegates_) {
			result += delegate(arg1, arg2);
		}
		return result;
	}

private:
	std::vector<DelegateFunc> delegates_;
};

// Static function to be used as a delegate
int DelegateFunc1(int arg1, int arg2) {
	return arg1 + arg2;
}

class MyClass {
public:
	int DelegateMethod(int arg1, int arg2) {
		return arg1 * arg2;
	}
};

int main() {
	Delegate delegateObj;

	// Add the static function as a delegate
	delegateObj.AddDelegate(&DelegateFunc1);

	// Create an instance of MyClass
	MyClass myObj;

	// Add the member function as a delegate using a lambda
	delegateObj.AddDelegate([&myObj](int arg1, int arg2) {
		return myObj.DelegateMethod(arg1, arg2);
		});

	// Invoke the delegate functions
	int result = delegateObj.InvokeDelegates(3, 4);
	std::cout << result << std::endl;  // Output: 19 (3 + 4) + (3 * 4) = 7 + 12 = 19

	return 0;
}


*/