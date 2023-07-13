#pragma once
class GameObject;
class Component
{
public:
	Component()	
	{

	}
	virtual ~Component()
	{

	}
private:
	GameObject* m_Owner;
public:
	GameObject* GetOwner() const { return m_Owner; }
	void SetOwner(GameObject* val) { m_Owner = val; }

};

