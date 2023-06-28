#pragma once

#include <vector>
#include "Object.h"
#include "Component.h"
#include "SceneComponent.h"
#include "AABB.h"

/*
	게임 오브젝트	 클래스
	World의 CreateGameObject<T>를 통해 생성된다.

	게임 오브젝트는 컴포넌트의 조합으로 이루어진다.
	게임 오브젝트의 위치는 Root로 설정한 SceneComponent를 통해 결정된다.
*/
class SceneComponent;
class Component;
class World;
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
	World* m_pOwnerWorld;
	bool m_bIsCullObject;
	bool m_bIsCulled;
	std::vector<Component*> m_OwnedComponents;
public:
	void SetRootComponent(SceneComponent* pRootComponent);
	SceneComponent* GetRootComponent() const;

	virtual void Update();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	D2D_VECTOR_2F GetWorldLocation();
	void SetWorldLocation(float x, float y);
	bool IsCullObject() const { return m_bIsCullObject; }
	// 루트에 있는 AABB를 오브젝트 전체를 대표하는 볼륨으로 사용합니다.
	const AABB& GetBoundingBox() const { return m_pRootComponent->GetBoundingBox(); }
	void SetBoundingBoxExtend(float x, float y) { m_pRootComponent->SetBoundingBoxExtend(x, y); }
	void SetIsCull(bool val) { m_bIsCulled = val; }

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
	World* GetOwnerWorld() const { return m_pOwnerWorld; }
	void SetOwnerWorld(World* val) { m_pOwnerWorld = val; }
};

