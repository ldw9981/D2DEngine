#pragma once

#include <vector>
#include "Object.h"
#include "../D2DRenderer/Component.h"

class SceneComponent;
class Component;
class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject()
	{
		for (auto& pComponent : m_OwnedComponents)
		{
			delete pComponent;
		}
		m_OwnedComponents.clear();
	}

protected:
	SceneComponent* m_pRootComponent;
	GameObject* m_pParentObject;

	std::vector<Component*> m_OwnedComponents;
public:
	void SetRootComponent(SceneComponent* pRootComponent);
	SceneComponent* GetRootComponent() const;

	virtual void Update();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	D2D_VECTOR_2F GetLocation();
	void SetLocation(float x, float y);

	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);
		T* pComponent = new T;
		pComponent->SetOwner(this);
		m_OwnedComponents.push_back(pComponent);
		return pComponent;
	}

	void SetParentObject(GameObject* pParentObject);
};

