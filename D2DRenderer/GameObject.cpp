#include "pch.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "GameApp.h"
#include "SceneComponent.h"
#include "RenderComponent.h"
#include "Component.h"
#include <fstream>
#include "Helper.h"


GameObject::GameObject()
	:m_pRootComponent(nullptr), m_IsCullObject(true),
	m_pParentObject(nullptr)
{

}

void GameObject::SetRootComponent(SceneComponent* pRootComponent)
{
	m_pRootComponent = pRootComponent;
}

SceneComponent* GameObject::GetRootComponent() const
{
	return m_pRootComponent;
}

void GameObject::Update()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Update();
	}
}

void GameObject::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		// 보관하고 있는 컴포넌트 인스턴스가 SceneComponent 일때만 Render를 호출한다.
		RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent);
		if (pRenderComponent)
		{
			pRenderComponent->Render(pRenderTarget);
		}
	}
}

D2D_VECTOR_2F GameObject::GetWorldLocation()
{
	return m_pRootComponent ? m_pRootComponent->GetRelativeLocation() : D2D_VECTOR_2F();
}

void GameObject::SetWorldLocation(const mathHelper::Vector2F& Location)
{
	if (m_pRootComponent)
	{
		m_pRootComponent->SetRelativeLocation(Location);
	}
}

void GameObject::SetParentObject(GameObject* pParentObject)
{
	if (pParentObject == nullptr)
	{
		m_pParentObject = nullptr;
		if (m_pRootComponent)
		{
			m_pRootComponent->SetParentScene(nullptr);
		}
		return;
	}
	
	// 부모설정하고  루트끼리 부모-자식 연결 시킨다. 
	m_pParentObject = pParentObject;
	SceneComponent* pRootComponent = pParentObject->GetRootComponent();
	assert(pRootComponent != nullptr);
	assert(m_pRootComponent != nullptr);
	
	if (m_pRootComponent)
	{
		m_pRootComponent->SetParentScene(pRootComponent);
	}
}

void GameObject::TakeDamage(float Damage, GameObject* pAttacker)
{
	m_OnTakeDamage.InvokeCallbacks(Damage, pAttacker);
}

void GameObject::SerializeOut(nlohmann::ordered_json& object)
{
	std::string type = typeid(*this).name();
	object["ClassName"] = D2DHelper::GetNameFromTypeName(type);
	
	if (m_pRootComponent)
	{
		object["RootComponent"] = m_pRootComponent->GetName();
	}
	else
	{
		object["RootComponent"] = "";
	}

	for (auto& pComponent : m_OwnedComponents)
	{
		nlohmann::ordered_json objComponent;
		pComponent->SerializeOut(objComponent);
		object["m_OwnedComponents"].push_back(objComponent);
	}
}

void GameObject::SerializeIn(nlohmann::ordered_json& object)
{
	std::string ComponentName;
	for (auto& JsonObjComponent : object["m_OwnedComponents"])
	{
		ComponentName = JsonObjComponent["m_Name"].get<std::string>();
		Component* pComponent = GetComponent(ComponentName);
		if (pComponent)
		{
			pComponent->SerializeIn(JsonObjComponent);
		}
	}
}

void GameObject::Save(const wchar_t* FilePath)
{
	nlohmann::ordered_json obj;
	SerializeOut(obj);
	std::ofstream ofs(FilePath);
	ofs << obj.dump(2);
	ofs.close();
}

