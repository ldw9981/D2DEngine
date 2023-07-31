#pragma once


#include "Object.h"
#include "Component.h"
#include "SceneComponent.h"
#include "AABB.h"
#include "Deligator.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "Object.h"
/*
	게임 오브젝트	 클래스
	World의 CreateGameObject<T>를 통해 생성된다.

	게임 오브젝트는 컴포넌트의 조합으로 이루어진다.
	게임 오브젝트의 위치는 Root로 설정한 SceneComponent를 통해 결정된다.
*/
class SceneComponent;
class Component;
class World;
class GameObject : public IAnimationNotify, public IColliderNotify , public Object
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
	SceneComponent* m_pRootComponent;		// 컴포넌트 중에 어느게 루트인지 설정
	GameObject* m_pParentObject;			// 월드에서 따라갈 오브젝트
	World* m_pOwnerWorld;					// 이 게임 오브젝트가 속한 월드
	bool m_IsCullObject;					// 컬링할수 있는 오브젝트 인지 확인
	bool m_IsNoCollider;						// 충돌을 하지 않는 오브젝트 인지 확인
	std::vector<Component*> m_OwnedComponents;	// 소유한 컴포넌트들

	DeligatorParam2<float, GameObject*> m_OnTakeDamage;
public:
	// 루트 컴포넌트로 설정
	void SetRootComponent(SceneComponent* pRootComponent);
	SceneComponent* GetRootComponent() const;

	virtual void Update(float DeltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	// 루트 SceneComponent의 위치를 반환합니다.
	D2D_VECTOR_2F GetWorldLocation();

	// 루트 SceneComponent의 위치를 설정합니다.
	void SetWorldLocation(const mathHelper::Vector2F& Location);

	// 컬링할수 있는 오브젝트 인지 확인합니다.
	bool IsCullObject() const { return m_IsCullObject; }
	bool IsNoCollide() const { return m_IsNoCollider; }

	// 루트에 있는 AABB를 오브젝트 전체를 대표하는 볼륨으로 사용합니다.
	const AABB& GetBoundingBox() const { return m_pRootComponent->GetBoundingBox(); }
	void SetBoundingBoxExtend(float x, float y) { m_pRootComponent->SetBoundingBoxExtend(x, y); }
	
	// 컴포넌트를 템틀릿 함수로 생성합니다.
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

	// 월드에서 따라갈 오브젝트를 설정합니다.
	void SetParentObject(GameObject* pParentObject);

	// 이 게임 오브젝트를 생성한 월드를 반환합니다.
	World* GetOwner() const { return m_pOwnerWorld; }

	// 이 게임 오브젝트가 속한 월드를 설정 합니다.
	void SetOwner(World* val) { m_pOwnerWorld = val; }

	const std::vector<Component*>& GetOwnedComponents() const { return m_OwnedComponents; }
	
	void TakeDamage(float Damage,GameObject* pAttacker);

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);

	virtual void Save(const wchar_t* FileName);

	virtual void OnBeginPlay();
	virtual void OnEndPlay();
};

