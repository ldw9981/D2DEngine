#include "pch.h"
#include "Component.h"
#include "Helper.h"

/*
	����� ����Ұ��ΰ�.
	�ĺ��� �ʿ��Ѱ�. �⺻���� �����ؾ��ϴ°�.
*/
void Component::SerializeOut(nlohmann::ordered_json& object)
{
	std::string type = typeid(*this).name();
	object["ClassName"] = D2DHelper::GetNameFromTypeName(type);
	object["m_Name"] = m_Name;
}

// ����� �����Ұ��ΰ�.
// JSON���� ������Ʈ�� �� ������ �ʿ��Ѱ� ���� �����Ų��. 
void Component::SerializeIn(nlohmann::ordered_json& object)
{
	
}
