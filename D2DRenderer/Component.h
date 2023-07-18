#pragma once
#include "Object.h"
#include <typeinfo>

/*
	게임 오브젝트의 기능을 컴포넌트 단위로 분리하기 위한 추상 클래스
	게임오브젝트는 컴포넌트의 조합으로 이루어진다.
	컴포넌트의 생성은 GameObject의 CreateComponent<T> 를 통해 이루어진다.

	지금당장은 Object의 역할이 없으므로 Object를 상속받지 않는다.
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

