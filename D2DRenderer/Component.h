#pragma once
#include "Object.h"
#include <typeinfo>

/*
	게임 오브젝트의 기능을 컴포넌트 단위로 분리하기 위한 추상 클래스
	게임오브젝트는 컴포넌트의 조합으로 이루어진다.
	컴포넌트의 생성은 GameObject의 CreateComponent<T> 를 통해 이루어진다.
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
	std::string m_Name;			// 게임 오브젝트 안에서 같은 종류의 컴포넌트라도 다른 이름을 갖게하여 구분할수 있게 한다.	
public:
	const std::string& GetName() const { return m_Name; }
	virtual void Update(float DeltaTime) = 0;
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
	GameObject* GetOwner() { return m_pOwner; }

	

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);

	virtual void OnBeginPlay() = 0;
	virtual void OnEndPlay() = 0;
};

