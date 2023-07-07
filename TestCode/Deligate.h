#pragma once

class MyComponent3;
class MyComponent4;

class Deligate {
public:
	using CallbackFunction = std::function<void(int)>;
	using CallbackMap = std::map<uintptr_t, CallbackFunction>;

	template <typename Class>
	void RemoveCallback(Class* instance) {
		callbacks_.erase(reinterpret_cast<uintptr_t>(instance));
	}

	void InvokeCallbacks(int value) {
		for (const auto& pair : callbacks_) {
			pair.second(value);
		}
	}

	template <typename Class, typename Function>
	void AddCallback(Class* instance, Function&& function) {
		CallbackFunction callback = [instance, function](int value) {
			(instance->*function)(value);
		};
		callbacks_[reinterpret_cast<uintptr_t>(instance)] = callback;
	}

private:
	CallbackMap callbacks_;
};

template<typename T>
class Deligate1 {
public:
	using CallbackFunction = std::function<void(T)>;
	using CallbackMap = std::map<uintptr_t, CallbackFunction>;

	template <typename Class>
	void RemoveCallback(Class* instance) {
		callbacks_.erase(reinterpret_cast<uintptr_t>(instance));
	}

	void InvokeCallbacks(T value) {
		for (const auto& pair : callbacks_) {
			pair.second(value);
		}
	}

	template <typename Class, typename Function>
	void AddCallback(Class* instance, Function&& function) {
		CallbackFunction callback = [instance, function](T value) {
			(instance->*function)(value);
		};
		callbacks_[reinterpret_cast<uintptr_t>(instance)] = callback;
	}

private:
	CallbackMap callbacks_;
};

template<typename T1,typename T2>
class Deligate2 {
public:
	using CallbackFunction = std::function<void(T1,T2)>;
	using CallbackMap = std::map<uintptr_t, CallbackFunction>;

	template <typename Class>
	void RemoveCallback(Class* instance) {
		callbacks_.erase(reinterpret_cast<uintptr_t>(instance));
	}

	void InvokeCallbacks(T1 value1,T2 value2) {
		for (const auto& pair : callbacks_) {
			pair.second(value1,value2);
		}
	}

	template <typename Class, typename Function>
	void AddCallback(Class* instance, Function&& function) {
		CallbackFunction callback = [instance, function](T1 value1,T2 value2) {
			(instance->*function)(value1,value2);
		};
		callbacks_[reinterpret_cast<uintptr_t>(instance)] = callback;
	}

private:
	CallbackMap callbacks_;
};