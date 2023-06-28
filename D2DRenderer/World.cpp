#include "pch.h"
#include "World.h"
#include "CameraComponent.h"
#include "CameraGameObject.h"
#include "D2DRenderer.h"

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
	// Render ȣ�� ���� �ø��� �Ѵ�.
	m_nCullCount=0;
	CullGameObject();

	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject->IsCulled())
		{
			m_nCullCount++;
			gameObject->Render(pRernderTarget);
		}
	}
	
	pRernderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	wstring strCullCount = L"Cull Count : " + to_wstring(m_nCullCount);
	D2DRenderer::m_Instance->DrawText(pRernderTarget,strCullCount, D2D1::RectF(0,0,300,50), D2D1::ColorF(D2D1::ColorF::White));
}

void World::CullGameObject()
{
	// ī�޶� ������ �ø��� ���� �ʴ´�.
	if (m_pCamera == nullptr)
	{
		return;
	}
	const AABB bbCamera = m_pCamera->GetBoundingBox();
		
	for (auto& gameObject : m_GameObjects)
	{
		// �ø��� ���� �ʴ´ٸ� ���� ������Ʈ�� �Ѿ��.
		if (gameObject->IsCullObject() == false)
		{
			continue;
		}

		// ��ħ Ȯ��
		const AABB bbGameObject = gameObject->GetBoundingBox();
		if (bbCamera.CheckIntersect(bbGameObject))
		{
			gameObject->SetIsCull(true);
		}
		else
		{
			gameObject->SetIsCull(false);
		}
	}
}
