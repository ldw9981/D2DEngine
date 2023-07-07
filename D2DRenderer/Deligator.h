#pragma once
#pragma once

#include <functional>
#include <map>

template<typename T>
class DeligatorParam1{
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

template<typename T1, typename T2>
class DeligatorParam2 {
public:
	using CallbackFunction = std::function<void(T1, T2)>;
	using CallbackMap = std::map<uintptr_t, CallbackFunction>;

	template <typename Class>
	void RemoveCallback(Class* instance) {
		callbacks_.erase(reinterpret_cast<uintptr_t>(instance));
	}

	void InvokeCallbacks(T1 value1, T2 value2) {
		for (const auto& pair : callbacks_) {
			pair.second(value1, value2);
		}
	}

	template <typename Class, typename Function>
	void AddCallback(Class* instance, Function&& function) {
		CallbackFunction callback = [instance, function](T1 value1, T2 value2) {
			(instance->*function)(value1, value2);
		};
		callbacks_[reinterpret_cast<uintptr_t>(instance)] = callback;
	}

private:
	CallbackMap callbacks_;
};

template<typename T1, typename T2, typename T3>
class DeligatorParam3 {
public:
	using CallbackFunction = std::function<void(T1, T2, T3)>;
	using CallbackMap = std::map<uintptr_t, CallbackFunction>;

	template <typename Class>
	void RemoveCallback(Class* instance) {
		callbacks_.erase(reinterpret_cast<uintptr_t>(instance));
	}

	void InvokeCallbacks(T1 value1, T2 value2, T3 value3) {
		for (const auto& pair : callbacks_) {
			pair.second(value1, value2, value3);
		}
	}

	template <typename Class, typename Function>
	void AddCallback(Class* instance, Function&& function) {
		CallbackFunction callback = [instance, function](T1 value1, T2 value2, T3 value3) {
			(instance->*function)(value1, value2, value3);
		};
		callbacks_[reinterpret_cast<uintptr_t>(instance)] = callback;
	}

private:
	CallbackMap callbacks_;
};
