#include "pch.h"
#include "World.h"
#include "CameraComponent.h"
#include "CameraGameObject.h"
#include "D2DRenderer.h"
#include "RenderComponent.h"

World::World()
{
}

void World::Update()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Update();
	}
}

void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	assert(m_pCamera != nullptr);
	// ī�޶� ��ǥ��� �̵��ϱ� ���� ���� ī�޶��� ����� ����
	const D2D1_MATRIX_3X2_F matCameraWorld = m_pCamera->GetWorldTransform();
	D2DRenderer::m_Instance->SetCameraTransform(matCameraWorld);	
	

	// Render ȣ�� ���� �ø��� �Ѵ�.
	m_nCullCount=0;



	const AABB bbCamera = m_pCamera->GetBoundingBox();
	for (auto& gameObject : m_GameObjects)
	{				
		// ī�޶� ������ ��ħ �׽�Ʈ		
		const AABB& bbGameObject = gameObject->GetBoundingBox();
		if (gameObject->IsCullObject() && !bbCamera.CheckIntersect(bbGameObject))
			continue;
			
		const std::vector<Component*> components = gameObject->GetOwnedComponents();
		for (auto& component : components)
		{			
			RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(component);
			if (pRenderComponent == nullptr)
				continue;

			D2DRenderer::m_Instance->AddRenderQueue(pRenderComponent);
		}
	}
	
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	wstring strCullCount = L"Cull Count : " + to_wstring(m_nCullCount);
	D2DRenderer::m_Instance->DrawText(pRenderTarget,strCullCount, D2D1::RectF(0,0,300,50), D2D1::ColorF(D2D1::ColorF::White));
}
