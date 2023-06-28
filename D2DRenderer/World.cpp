#include "pch.h"
#include "World.h"
#include "CameraComponent.h"
#include "CameraGameObject.h"

World::World()
{
}

bool World::Initialize()
{
	return true;
}

void World::Update()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Update();
	}
}

void World::Render(ID2D1RenderTarget* pRernderTarget)
{
	CullGameObject();

	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Render(pRernderTarget);
	}
}

void World::CullGameObject()
{
	// 카메라가 없으면 컬링을 하지 않는다.
	if (m_pCamera == nullptr)
	{
		return;
	}

	// 카메라의 위치를 기준으로 컬링을 한다.
	D2D_VECTOR_2F cameraLocation = m_pCamera->GetWorldLocation();
	D2D_VECTOR_2F cameraExtend = m_pCamera->GetBoundingBox().m_Extend;

	// 카메라의 위치를 기준으로 컬링을 한다.
	for (auto& gameObject : m_GameObjects)
	{
		// 컬링을 하지 않는다면 다음 오브젝트로 넘어간다.
		if (gameObject->IsCullObject() == false)
		{
			continue;
		}

		if (gameObject->GetBoundingBox().CheckIntersect(m_pCamera->GetBoundingBox()))
		{
			gameObject->SetIsCull(true);
		}
		else
		{
			gameObject->SetIsCull(false);
		}
	}
}
