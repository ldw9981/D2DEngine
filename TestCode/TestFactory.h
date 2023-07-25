#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional> // For std::function


int TestFactory();

// Registration macros to simplify registration of concrete products
#define REGISTER_PRODUCT(ProductType) \
    GameObject* create##ProductType() { return new ProductType(); } \
    bool registered##ProductType = ProductFactory::registerProduct(#ProductType, create##ProductType);

class GameObject;
// Factory class using registration mechanism
class ProductFactory {
public:
	using ProductCreator = std::function<GameObject* ()>;

	static GameObject* createProduct(const std::string& productType) {
		auto it = getRegistry().find(productType);
		if (it != getRegistry().end()) {
			return it->second();
		}
		return nullptr;
	}

	static bool registerProduct(const std::string& productType, ProductCreator creator) {
		getRegistry()[productType] = creator;
		return true;
	}

private:
	static std::map<std::string, ProductCreator>& getRegistry() {
		static std::map<std::string, ProductCreator> registry;
		return registry;
	}
};

