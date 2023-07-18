#pragma once
/*
	오브젝트의 모든 공통 기능을 정의하는 추상 클래스
	추후 Save/Load를 하는 Serialize을 선언할 예정
	자식 클래스는 Serialize를 구현해야 한다.
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
		return	self.name();
	}

	virtual void SerializeOut(nlohmann::ordered_json& object)=0;
	virtual void SerializeIn(nlohmann::ordered_json& object)=0;
};

