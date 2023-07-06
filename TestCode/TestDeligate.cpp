#include <iostream>
#include <functional>
#include <map>

class MyClass {
public:
    std::wstring m_Text = L"MyClass";
public:
    void CallbackFunction(int value) {
        std::cout << "Callback called with value: " << this << " " << value << std::endl;
    }
};

class Delegate {
public:
    using CallbackFunction = std::function<void(int)>;
    using CallbackMap = std::map<MyClass*, CallbackFunction>;

    void AddCallback(MyClass* instance, const CallbackFunction& callback) {
        callbacks_[instance] = callback;
    }

    void RemoveCallback(MyClass* instance) {
        callbacks_.erase(instance);
    }

    void InvokeCallbacks(int value) {
        for (const auto& pair : callbacks_) {
            pair.second(value);
        }
    }

private:
    CallbackMap callbacks_;
};

int main() {
    MyClass myObject1;
    MyClass myObject2;
    Delegate delegate;

    auto a = std::bind(&MyClass::CallbackFunction, &myObject1, std::placeholders::_1);
    std::cout << "te " << std::endl;

    delegate.AddCallback(&myObject1, std::bind(&MyClass::CallbackFunction, &myObject1, std::placeholders::_1));
    delegate.AddCallback(&myObject2, std::bind(&MyClass::CallbackFunction, &myObject2, std::placeholders::_1));

    // Invoke the callbacks
    delegate.InvokeCallbacks(42);

    // Remove the callback for myObject2
    delegate.RemoveCallback(&myObject2);

    // Invoke the callbacks again
    delegate.InvokeCallbacks(42);

    return 0;
}
