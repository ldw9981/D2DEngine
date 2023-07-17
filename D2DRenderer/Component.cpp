#include "pch.h"
#include "Component.h"


void Component::SerializeOut(nlohmann::ordered_json& object)
{
	object["ClassName"] = GetClassName();
	object["m_ComponentName"] = m_ComponentName;
}
