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
	// Render 호출 전에 컬링을 한다.
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
	// 카메라가 없으면 컬링을 하지 않는다.
	if (m_pCamera == nullptr)
	{
		return;
	}
	const AABB bbCamera = m_pCamera->GetBoundingBox();
		
	for (auto& gameObject : m_GameObjects)
	{
		// 컬링을 하지 않는다면 다음 오브젝트로 넘어간다.
		if (gameObject->IsCullObject() == false)
		{
			continue;
		}

		// 겹침 확인
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
