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

	virtual bool Initialize() override;
	virtual void Update() override;
	void Render(ID2D1RenderTarget* pRernderTarget);
protected:
    std::list<GameObject*> m_GameObjects;

public:
    template<typename T>
	T* CreateGameObject()
	{
		T* newObject = new T();
		m_GameObjects.push_back(newObject);
		return newObject;
	}
};

