#include "pch.h"
#include "World.h"
#include "CameraComponent.h"
#include "Camera.h"
#include "D2DRenderer.h"
#include "RenderComponent.h"
#include "ColliderComponent.h"	
#include "BoxComponent.h"	
#include "Helper.h"
#include "Bitmap.h"
#include "Effect.h"

World::World(std::string Name)
	:m_Name(Name)
{
	World::RegistGameObjectClass<Camera>();
	World::RegistGameObjectClass<Effect>();
	World::RegistGameObjectClass<Bitmap>();
}

/*
	매프레임 BoxComponent를 모으는건 비효율 적이다.
	CollisionWorld를 따로 두면 해결되지만 이해하기 쉽게 일단 이렇게 구현
*/
void World::Update()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Update();
	}  

	// 현재 월드에서 모든 게임오브젝트의 BoxComponent를 모은다.
	std::vector<ColliderComponent*> colliderComponents;
	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject->IsNoCollide())	//충돌없음은 패스
			continue;	
		
		const std::vector<Component*> components = gameObject->GetOwnedComponents();
		for (auto& component : components)
		{
			ColliderComponent* pColliderComponent = dynamic_cast<ColliderComponent*>(component);
			if (pColliderComponent == nullptr)
				continue;

			//  그리는 용도면 패스
			if(pColliderComponent->GetCollisionType() == CollisionType::NoCollision)
				continue;

			pColliderComponent->ClearAndBackupCollideState();
			colliderComponents.push_back(pColliderComponent);
		}
	}

	// 충돌 테스트
	for (size_t source = 0; source < colliderComponents.size(); source++)
	{
		for (size_t target = source +1; target < colliderComponents.size(); target++)
		{
			// 같은 게임 오브젝트면 패스
			if (colliderComponents[source]->GetOwner() == colliderComponents[target]->GetOwner())
				continue;

			// 충돌 안하면 패스
			if (!colliderComponents[source]->IsCollide(colliderComponents[target]))
				continue;

			if (colliderComponents[source]->GetCollisionType() == CollisionType::Block &&
				colliderComponents[target]->GetCollisionType() == CollisionType::Block 	)
			{
				// 충돌 처리
				colliderComponents[source]->ProcessBlock(colliderComponents[target]);
				colliderComponents[target]->ProcessBlock(colliderComponents[source]);
			}
			else
			{
				colliderComponents[source]->InsertCollideState(colliderComponents[target]);
				colliderComponents[target]->InsertCollideState(colliderComponents[source]);
			}
		}
	}

	// Begin/End 처리
	for (auto& pColliderComponent : colliderComponents)
	{
		pColliderComponent->ProcessOverlap();
	}
	
}


/*	
	Todo : 게임 오브젝트에서  RenderComponent를 모으기위해 매번 dynamic_cast 사용 하지않는 방법을 찾아보자
*/
void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	assert(m_pCamera != nullptr);
	// 카메라 좌표계로 이동하기 위한 현재 카메라의 역행렬 설정
	const D2D1_MATRIX_3X2_F matCameraWorld = m_pCamera->GetWorldTransform();
	D2DRenderer::m_Instance->SetCameraTransform(matCameraWorld);	
	
	// 초기화
	m_nCulledObjectCount =0;
	m_RenderQueue.clear();
	
	const AABB bbCamera = m_pCamera->GetBoundingBox();
	for (auto& gameObject : m_GameObjects)
	{				
		// 게임 오브젝트와 카메라 겹침 테스트 
		const AABB& bbGameObject = gameObject->GetBoundingBox();
		if (!gameObject->IsCullObject())
			continue;
		
		if (!bbCamera.CheckIntersect(bbGameObject))
			continue;
			
		// 겹치면 내부 RenderComponent Ptr를 큐에 보관
		m_nCulledObjectCount++;
		const std::vector<Component*> components = gameObject->GetOwnedComponents();
		for (auto& component : components)
		{			
			RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(component);
			if (pRenderComponent == nullptr)
				continue;

			m_RenderQueue.push_back(pRenderComponent);			
		}
	}
	
	// RenderCoomponent 그릴 순서 정렬
	std::sort(m_RenderQueue.begin(), m_RenderQueue.end(), RenderComponent::CompareRenderOrder);

	// 렌더큐를 순회하면서 렌더링한다.
	for (auto& pRenderComponent : m_RenderQueue)
	{
		pRenderComponent->Render(pRenderTarget);
	}

	// 텍스트 정보 출력
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	std::wstring strCullCount = L"Culled Object Count : " + std::to_wstring(m_nCulledObjectCount);
	D2DRenderer::m_Instance->DrawText(pRenderTarget,strCullCount, D2D1::RectF(0,0,300,50), D2D1::ColorF(D2D1::ColorF::White));
}

void World::SerializeOut(nlohmann::ordered_json& object)
{
	object["m_Name"] = m_Name;
	for (auto& gameObject : m_GameObjects)
	{
		nlohmann::ordered_json JsonGameObject;
		gameObject->SerializeOut(JsonGameObject);
		object["m_GameObjects"].push_back(JsonGameObject);
	}
}

void World::SerializeIn(nlohmann::ordered_json& object)
{
	m_Name = object["m_Name"].get<std::string>();
	for (auto& JsonGameObj : object["m_GameObjects"])
	{
		std::string ClassName = JsonGameObj["ClassName"].get<std::string>();
		// Todo: ClassName으로 게임오브젝트를 생성하고 SerializeIn호출한다.
		// 다른 프로젝트에 있는 게임오브젝트도 생성하려면 어떻게 해야할까..
		GameObject* pGameObject = World::CreateGameObject(ClassName);
		if (pGameObject)
		{
			pGameObject->SerializeIn(JsonGameObj);
		}		
	}
}

void World::Save(const wchar_t* FilePath)
{
	nlohmann::ordered_json obj;
	SerializeOut(obj);
	std::ofstream ofs(FilePath);
	ofs << obj.dump(2);
	ofs.close();
}

bool World::Load(const wchar_t* FilePath)
{
	std::ifstream ifs(FilePath, std::ios::in);
	if (!ifs.is_open())
	{
		LOG_ERROR(L"File not found %s", FilePath);
		return false;
	}
	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	nlohmann::ordered_json obj = nlohmann::ordered_json::parse(str);

	SerializeIn(obj);

	return true;
}

GameObject* World::CreateGameObject(const std::string& ClassName)
{
	GameObject* newObject = nullptr;
	auto iter = m_ClassCreatorFunction.find(ClassName);
	if (iter != m_ClassCreatorFunction.end())
	{
		auto func = iter->second;

		newObject = func();
		newObject->SetOwnerWorld(this);
		m_GameObjects.push_back(newObject);
	}
	return nullptr;
}

std::map<std::string, std::function<GameObject* ()>> World::m_ClassCreatorFunction;
