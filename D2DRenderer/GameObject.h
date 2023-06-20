#pragma once
#include <type_traits>
#include <vector>
#include "Object.h"
#include <d2d1_1.h>
#include "../D2DRenderer/Component.h"

class SceneComponent;
class Component;
class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject();

protected:
	SceneComponent* m_pRootComponent;
		
	std::vector<Component*> m_OwnedComponent;
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
		bool bIsComponent = std::is_base_of<Component, T>::value;
		//assert(bIsComponent==true);
		T* pComponent = new T;
		pComponent->SetOwner(this);
		m_OwnedComponent.push_back(pComponent);
		return pComponent;
	}
};

