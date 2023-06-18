#pragma once
#include "Object.h"
#include <list>
#include "GameObject.h"
class World :
    public Object
{
public:
    World();
    virtual ~World();

	virtual bool Init() override;
	virtual void Update() override;
	void Render(ID2D1RenderTarget* pRernderTarget);
protected:
    std::list<GameObject*> m_GameObjectContainer;

public:
    template<typename T>
	T* CreateGameObject()
	{
		T* newObject = new T();
		m_GameObjectContainer.push_back(newObject);
		return newObject;
	}
};

