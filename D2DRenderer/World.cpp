#include "pch.h"
#include "World.h"
#include "CameraComponent.h"
#include "CameraGameObject.h"
#include "D2DRenderer.h"

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
	// ī�޶� ��ǥ��� �̵��ϱ� ���� ���� ī�޶��� ����� ����
	if (m_pCamera!= nullptr)
	{
		const D2D1_MATRIX_3X2_F matCameraWorld = m_pCamera->GetWorldTransform();
		D2DRenderer::m_Instance->SetCameraTransform(matCameraWorld);	
	}

	// Render ȣ�� ���� �ø��� �Ѵ�.
	m_nCullCount=0;
	CullGameObject();

	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject->IsCulled())
		{
			m_nCullCount++;
			gameObject->Render(pRenderTarget);
		}
	}
	
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	wstring strCullCount = L"Cull Count : " + to_wstring(m_nCullCount);
	D2DRenderer::m_Instance->DrawText(pRenderTarget,strCullCount, D2D1::RectF(0,0,300,50), D2D1::ColorF(D2D1::ColorF::White));
}

void World::CullGameObject()
{
	const AABB bbCamera = m_pCamera->GetBoundingBox();		
	for (auto& gameObject : m_GameObjects)
	{
		// �ø��� ���� �ʴ´ٸ� ���� ������Ʈ�� �Ѿ��.
		if (gameObject->IsCullObject() == false)
			continue;
		
		// ī�޶� ������ �׳� �׸�
		if (m_pCamera == nullptr)
		{
			gameObject->SetIsCull(true);
			continue;
		}
		// ī�޶� ������ ��ħ �׽�Ʈ
		else
		{
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
}
