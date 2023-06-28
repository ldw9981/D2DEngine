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
	// ī�޶� ������ �ø��� ���� �ʴ´�.
	if (m_pCamera == nullptr)
	{
		return;
	}

	// ī�޶��� ��ġ�� �������� �ø��� �Ѵ�.
	D2D_VECTOR_2F cameraLocation = m_pCamera->GetWorldLocation();
	D2D_VECTOR_2F cameraExtend = m_pCamera->GetBoundingBox().m_Extend;

	// ī�޶��� ��ġ�� �������� �ø��� �Ѵ�.
	for (auto& gameObject : m_GameObjects)
	{
		// �ø��� ���� �ʴ´ٸ� ���� ������Ʈ�� �Ѿ��.
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
