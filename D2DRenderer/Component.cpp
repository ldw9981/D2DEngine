#include "pch.h"
#include "Component.h"
#include "Helper.h"

void Component::SerializeOut(nlohmann::ordered_json& object)
{
	std::string type = typeid(*this).name();
	object["ClassName"] = D2DHelper::GetNameFromTypeName(type);
	object["m_Name"] = m_Name;
}

void Component::SerializeIn(nlohmann::ordered_json& object)
{
	m_Name = object["m_Name"];
}
