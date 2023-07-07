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
	
	// �ʱ�ȭ
	m_nCulledObjectCount =0;
	m_RenderQueue.clear();
	
	const AABB bbCamera = m_pCamera->GetBoundingBox();
	for (auto& gameObject : m_GameObjects)
	{				
		// ���� ������Ʈ�� ī�޶� ��ħ �׽�Ʈ 
		const AABB& bbGameObject = gameObject->GetBoundingBox();
		if (gameObject->IsCullObject() && !bbCamera.CheckIntersect(bbGameObject))
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
	wstring strCullCount = L"Culled Object Count : " + to_wstring(m_nCulledObjectCount);
	D2DRenderer::m_Instance->DrawText(pRenderTarget,strCullCount, D2D1::RectF(0,0,300,50), D2D1::ColorF(D2D1::ColorF::White));
}
