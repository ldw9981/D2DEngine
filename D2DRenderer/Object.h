#pragma once
/*
	������Ʈ�� ��� ���� ����� �����ϴ� �߻� Ŭ����
	���� Save/Load�� �ϴ� Serialize�� ������ ����
	�ڽ� Ŭ������ Serialize�� �����ؾ� �Ѵ�.
*/
#include <nlohmann/json.hpp>

class Object
{
public:
	Object()
	{

	};
	virtual ~Object()
	{

	};

	std::string GetClassName()
	{
		const std::type_info& self = typeid(*this);
		std::string className = self.name();
		size_t classPos = className.find("class ");
		if (classPos != std::string::npos) {
			className.erase(classPos, 6); // 6 is the length of "class "
		}
		return className;
	}

	virtual void SerializeOut(nlohmann::ordered_json& object)=0;
	virtual void SerializeIn(nlohmann::ordered_json& object)=0;
};

