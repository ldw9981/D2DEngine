#include <iostream>
#include <string>
#include <map>
#include <functional> // For std::function

// Base class representing the product
class Product {
public:
	virtual void display() = 0;
	virtual ~Product() {}
};

// Concrete Product 1
class ConcreteProduct1 : public Product {
public:
	void display() override {
		std::cout << "Concrete Product 1" << std::endl;
	}
};

// Concrete Product 2
class ConcreteProduct2 : public Product {
public:
	void display() override {
		std::cout << "Concrete Product 2" << std::endl;
	}
};

// Factory class using registration mechanism
class ProductFactory {
public:
	using ProductCreator = std::function<Product* ()>;

	static Product* createProduct(const std::string& productType) {
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

// Registration macros to simplify registration of concrete products
#define REGISTER_PRODUCT(ProductType) \
    Product* create##ProductType() { return new ProductType(); } \
    bool registered##ProductType = ProductFactory::registerProduct(#ProductType, create##ProductType);

// Registration of concrete products
REGISTER_PRODUCT(ConcreteProduct1)
REGISTER_PRODUCT(ConcreteProduct2)

int TestFactory() {
	// Client code
	Product* product1 = ProductFactory::createProduct("ConcreteProduct1");
	if (product1) {
		product1->display();
		delete product1;
	}
	else {
		std::cout << "Invalid product type!" << std::endl;
	}

	Product* product2 = ProductFactory::createProduct("ConcreteProduct2");
	if (product2) {
		product2->display();
		delete product2;
	}
	else {
		std::cout << "Invalid product type!" << std::endl;
	}

	return 0;
}

