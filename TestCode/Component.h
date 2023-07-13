#pragma once
class GameObject;
class Component
{
public:
	Component()	
	{

	}
	~Component();

	GameObject* m_Owner;
};

