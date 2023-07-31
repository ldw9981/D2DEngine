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
#include "CameraComponent.h"
#include "Factory.h"
#include "Helper.h"

World::World(std::string Name)
	:m_Name(Name), m_pCamera(nullptr), m_Playing(false)
{

}

void World::OnBeginPlay()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->OnBeginPlay();
	}
	m_Playing = true;
		
	UpdateReferenceCameraComponent(m_CameraID);
}

void World::OnEndPlay()
{
	m_Playing = false;
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->OnEndPlay();
	}
}

/*
	�������� BoxComponent�� �����°� ��ȿ�� ���̴�.
	CollisionWorld�� ���� �θ� �ذ������ �����ϱ� ���� �ϴ� �̷��� ����
*/
void World::Update(float DeltaTime)
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Update(DeltaTime);
	}  

	// ���� ���忡�� ��� ���ӿ�����Ʈ�� BoxComponent�� ������.
	std::vector<ColliderComponent*> colliderComponents;
	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject->IsNoCollide())	//�浹������ �н�
			continue;	
		
		const std::vector<Component*> components = gameObject->GetOwnedComponents();
		for (auto& component : components)
		{
			ColliderComponent* pColliderComponent = dynamic_cast<ColliderComponent*>(component);
			if (pColliderComponent == nullptr)
				continue;

			//  �׸��� �뵵�� �н�
			if(pColliderComponent->GetCollisionType() == CollisionType::NoCollision)
				continue;

			pColliderComponent->ClearAndBackupCollideState();
			colliderComponents.push_back(pColliderComponent);
		}
	}

	// �浹 �׽�Ʈ
	for (size_t source = 0; source < colliderComponents.size(); source++)
	{
		for (size_t target = source +1; target < colliderComponents.size(); target++)
		{
			// ���� ���� ������Ʈ�� �н�
			if (colliderComponents[source]->GetOwner() == colliderComponents[target]->GetOwner())
				continue;

			// �浹 ���ϸ� �н�
			if (!colliderComponents[source]->IsCollide(colliderComponents[target]))
				continue;

			if (colliderComponents[source]->GetCollisionType() == CollisionType::Block &&
				colliderComponents[target]->GetCollisionType() == CollisionType::Block 	)
			{
				// �浹 ó��
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

	// Begin/End ó��
	for (auto& pColliderComponent : colliderComponents)
	{
		pColliderComponent->ProcessOverlap();
	}
	
}


/*	
	Todo : ���� ������Ʈ����  RenderComponent�� ���������� �Ź� dynamic_cast ��� �����ʴ� ����� ã�ƺ���
*/
void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	assert(m_pCamera != nullptr);
	// ī�޶� ��ǥ��� �̵��ϱ� ���� ���� ī�޶��� ����� ����
	const D2D1_MATRIX_3X2_F matCameraWorld = m_pCamera->GetWorldTransform();
	D2DRenderer::m_Instance->SetCameraTransform(matCameraWorld);	
	
	// �ʱ�ȭ
	m_nCulledObjectCount =0;
	m_RenderQueue.clear();
	
	const AABB bbCamera = m_pCamera->GetBoundingBox();
	for (auto& gameObject : m_GameObjects)
	{				
		// ���� ������Ʈ�� ī�޶� ��ħ �׽�Ʈ 
		const AABB& bbGameObject = gameObject->GetBoundingBox();
		if (!gameObject->IsCullObject())
			continue;
		
		if (!bbCamera.CheckIntersect(bbGameObject))
			continue;
			
		// ��ġ�� ���� RenderComponent Ptr�� ť�� ����
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
	
	// RenderCoomponent �׸� ���� ����
	std::sort(m_RenderQueue.begin(), m_RenderQueue.end(), RenderComponent::CompareRenderOrder);

	// ����ť�� ��ȸ�ϸ鼭 �������Ѵ�.
	for (auto& pRenderComponent : m_RenderQueue)
	{
		pRenderComponent->Render(pRenderTarget);
	}

	// �ؽ�Ʈ ���� ���
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	std::wstring strCullCount = L"Culled Object Count : " + std::to_wstring(m_nCulledObjectCount);
	D2DRenderer::m_Instance->DrawText(pRenderTarget,strCullCount, D2D1::RectF(0,0,300,50), D2D1::ColorF(D2D1::ColorF::White));
}

void World::SetCameraID(int id)
{	
	if (m_Playing)
	{
		if (UpdateReferenceCameraComponent(id))
		{
			m_CameraID = id;
		}
	}
	else
	{
		m_CameraID = id;
	}
}

bool World::UpdateReferenceCameraComponent(int id)
{
	for (auto& it : m_Cameras)
	{
		if (it->GetCameraID() == id)
		{
			m_pCamera = it;
			return true;
		}
	}
	LOG_ERROR(L"Camera ID  %d is not exist", m_CameraID);	
	return false;
}

void World::SerializeOut(nlohmann::ordered_json& object)
{
	object["m_Name"] = m_Name;
	object["m_CameraID"] = m_CameraID;
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
	m_CameraID = object["m_CameraID"].get<int>();
	for (auto& JsonGameObj : object["m_GameObjects"])
	{
		std::string ClassName = JsonGameObj["ClassName"].get<std::string>();
		// Todo: ClassName���� ���ӿ�����Ʈ�� �����ϰ� SerializeInȣ���Ѵ�.
		// �ٸ� ������Ʈ�� �ִ� ���ӿ�����Ʈ�� �����Ϸ��� ��� �ؾ��ұ�..
		GameObject* pGameObject = Factory::CreateGameObject(ClassName);
		if (pGameObject)
		{
			pGameObject->SetOwner(this);
			pGameObject->SerializeIn(JsonGameObj);
			m_GameObjects.push_back(pGameObject);
		}	
		else
		{
			LOG_ERROR(L"Failed to create GameObject %s", D2DHelper::StringToWString(ClassName).c_str());
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

void World::AddCamera(CameraComponent* pCameraComponent)
{
	auto it = std::find(m_Cameras .begin(), m_Cameras.end(), pCameraComponent);
	if (it != m_Cameras.end())
	{
		LOG_ERROR(L"CameraComponent is already added. \n");
		return;
	}
	m_Cameras.push_back(pCameraComponent);
}

void World::DelCamera(CameraComponent* pCameraComponent)
{
	auto it = std::find(m_Cameras.begin(), m_Cameras.end(), pCameraComponent);
	if (it == m_Cameras.end())
	{
		LOG_ERROR(L"CameraComponent is none. \n");
		return;
	}
	m_Cameras.remove(pCameraComponent);
}