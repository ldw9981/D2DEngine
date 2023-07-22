#include "pch.h"
#include "Component.h"
#include "Helper.h"

/*
	어떤값을 출력할것인가.
	식별이 필요한값. 기본값을 수정해야하는값.
*/
void Component::SerializeOut(nlohmann::ordered_json& object)
{
	std::string type = typeid(*this).name();
	object["ClassName"] = D2DHelper::GetNameFromTypeName(type);
	object["m_Name"] = m_Name;
}

// 어떤값을 적용할것인가.
// JSON으로 컴포넌트에 꼭 변경이 필요한가 값을 적용시킨다. 
void Component::SerializeIn(nlohmann::ordered_json& object)
{
	
}
