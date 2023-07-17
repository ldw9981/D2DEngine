#pragma once


#include "Object.h"
#include "Component.h"
#include "SceneComponent.h"
#include "AABB.h"
#include "Deligator.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
/*
	���� ������Ʈ	 Ŭ����
	World�� CreateGameObject<T>�� ���� �����ȴ�.

	���� ������Ʈ�� ������Ʈ�� �������� �̷������.
	���� ������Ʈ�� ��ġ�� Root�� ������ SceneComponent�� ���� �����ȴ�.
*/
class SceneComponent;
class Component;
class World;
class GameObject : public IAnimationNotify, public IColliderNotify
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
	SceneComponent* m_pRootComponent;		// ������Ʈ �߿� ����� ��Ʈ���� ����
	GameObject* m_pParentObject;			// ���忡�� ���� ������Ʈ
	World* m_pOwnerWorld;					// �� ���� ������Ʈ�� ���� ����
	bool m_bIsCullObject;					// �ø��Ҽ� �ִ� ������Ʈ ���� Ȯ��
	bool m_IsNoCollide;						// �浹�� ���� �ʴ� ������Ʈ ���� Ȯ��
	std::vector<Component*> m_OwnedComponents;	// ������ ������Ʈ��

	DeligatorParam2<float, GameObject*> m_OnTakeDamage;
public:
	// ��Ʈ ������Ʈ�� ����
	void SetRootComponent(SceneComponent* pRootComponent);
	SceneComponent* GetRootComponent() const;

	virtual void Update();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	// ��Ʈ SceneComponent�� ��ġ�� ��ȯ�մϴ�.
	D2D_VECTOR_2F GetWorldLocation();

	// ��Ʈ SceneComponent�� ��ġ�� �����մϴ�.
	void SetWorldLocation(const mathHelper::Vector2F& Location);

	// �ø��Ҽ� �ִ� ������Ʈ ���� Ȯ���մϴ�.
	bool IsCullObject() const { return m_bIsCullObject; }
	bool IsNoCollide() const { return m_IsNoCollide; }

	// ��Ʈ�� �ִ� AABB�� ������Ʈ ��ü�� ��ǥ�ϴ� �������� ����մϴ�.
	const AABB& GetBoundingBox() const { return m_pRootComponent->GetBoundingBox(); }
	void SetBoundingBoxExtend(float x, float y) { m_pRootComponent->SetBoundingBoxExtend(x, y); }
	
	// ������Ʈ�� ��Ʋ�� �Լ��� �����մϴ�.
	template<typename T>
	T* CreateComponent(const std::string& Name )
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);
		T* pComponent = new T(this,Name);	
		m_OwnedComponents.push_back(pComponent);
		return pComponent;
	}

	Component* GetComponent(const std::string& Name)
	{
		for (auto& pComponent : m_OwnedComponents)
		{
			if (pComponent->GetName() == Name)
			{
				return pComponent;
			}
		}
		return nullptr;
	}

	// ���忡�� ���� ������Ʈ�� �����մϴ�.
	void SetParentObject(GameObject* pParentObject);

	// �� ���� ������Ʈ�� ������ ���带 ��ȯ�մϴ�.
	World* GetOwnerWorld() const { return m_pOwnerWorld; }

	// �� ���� ������Ʈ�� ���� ���带 ���� �մϴ�.
	void SetOwnerWorld(World* val) { m_pOwnerWorld = val; }

	const std::vector<Component*>& GetOwnedComponents() const { return m_OwnedComponents; }
	
	void TakeDamage(float Damage,GameObject* pAttacker);
};

