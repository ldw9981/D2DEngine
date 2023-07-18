#pragma once
#include "Object.h"
#include <typeinfo>

/*
	���� ������Ʈ�� ����� ������Ʈ ������ �и��ϱ� ���� �߻� Ŭ����
	���ӿ�����Ʈ�� ������Ʈ�� �������� �̷������.
	������Ʈ�� ������ GameObject�� CreateComponent<T> �� ���� �̷������.

	���ݴ����� Object�� ������ �����Ƿ� Object�� ��ӹ��� �ʴ´�.
*/
class GameObject;
class Component : public Object
{
public:
	Component(GameObject* pOwner,const std::string& Name) : m_pOwner(pOwner),m_Name(Name)
	{
	}
	virtual ~Component() {};

protected:
	GameObject* m_pOwner;
	std::string m_Name;
public:
	const std::string& GetName() const { return m_Name; }
	virtual void Update() = 0;
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
	GameObject* GetOwner() { return m_pOwner; }

	

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object) { };
};

