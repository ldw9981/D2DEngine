#include "pch.h"
#include "Component.h"


void Component::SerializeOut(nlohmann::ordered_json& object)
{
	object["m_Name"] = m_Name;
}
