#pragma once

#include <vector>
#include "Object.h"
#include "Component.h"
#include "SceneComponent.h"
#include "AABB.h"

/*
	���� ������Ʈ	 Ŭ����
	World�� CreateGameObject<T>�� ���� �����ȴ�.

	���� ������Ʈ�� ������Ʈ�� �������� �̷������.
	���� ������Ʈ�� ��ġ�� Root�� ������ SceneComponent�� ���� �����ȴ�.
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
	// ��Ʈ�� �ִ� AABB�� ������Ʈ ��ü�� ��ǥ�ϴ� �������� ����մϴ�.
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

