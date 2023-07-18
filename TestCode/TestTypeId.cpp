#include <iostream>
#include <typeinfo>

class Shape {
public:
	virtual void draw() {
		std::cout << "Drawing a shape." << std::endl;
	}

	virtual std::string GetTypeName()
	{
		const std::type_info& self = typeid(*this);
		return	self.name();
	}
};

class Rectangle : public Shape {
public:
	void draw() override {
		std::cout << "Drawing a rectangle." << std::endl;
	}
	
};

int TestTypeId()
{
	Shape shape;
	Rectangle rectangle;

	// Get the type_info objects for the classes
	const std::type_info& shapeTypeInfo = typeid(shape);
	const std::type_info& rectangleTypeInfo = typeid(rectangle);

	// Print the human-readable names of the classes
	std::cout << "Shape Class Name: " << shape.GetTypeName() << std::endl;
	std::cout << "Rectangle Class Name: " << rectangle.GetTypeName() << std::endl;

	// Test the relationship between the classes using typeid
	if (typeid(rectangle) == typeid(Shape)) {
		std::cout << "Rectangle is a Shape." << std::endl;
	}
	else {
		std::cout << "Rectangle is not a Shape." << std::endl;
	}

	return 0;
}
