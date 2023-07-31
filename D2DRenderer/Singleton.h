#pragma once

template <typename T>
class Singleton {
private:
	// Static pointer to the single instance
	static T* instance;

protected:
	// Protected constructor to prevent instantiation from outside the class
	Singleton() {
		// Constructor code (optional)
	}

public:
	// Static method to get the single instance
	static T* GetInstance() {
		// Create the instance if it doesn't exist
		if (!instance) {
			instance = new T;
		}
		return instance;
	}
};

// Initialize the static instance pointer to null
template <typename T>
T* Singleton<T>::instance = nullptr;