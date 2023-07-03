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
	// 카메라 좌표계로 이동하기 위한 현재 카메라의 역행렬 설정
	if (m_pCamera!= nullptr)
	{
		const D2D1_MATRIX_3X2_F matCameraWorld = m_pCamera->GetWorldTransform();
		D2DRenderer::m_Instance->SetCameraTransform(matCameraWorld);	
	}

	// Render 호출 전에 컬링을 한다.
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
		// 컬링을 하지 않는다면 다음 오브젝트로 넘어간다.
		if (gameObject->IsCullObject() == false)
			continue;
		
		// 카메라가 없으면 그냥 그림
		if (m_pCamera == nullptr)
		{
			gameObject->SetIsCull(true);
			continue;
		}
		// 카메라 있으면 겹침 테스트
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
