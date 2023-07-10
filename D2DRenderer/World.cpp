#include "pch.h"
#include "World.h"
#include "CameraComponent.h"
#include "CameraGameObject.h"
#include "D2DRenderer.h"
#include "RenderComponent.h"
#include "ColliderComponent.h"	
#include "BoxComponent.h"	

World::World()
{
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
	std::vector<BoxComponent*> colliderComponents;
	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject->IsNoCollide())	//충돌없음은 패스
			continue;	
		
		const std::vector<Component*> components = gameObject->GetOwnedComponents();
		for (auto& component : components)
		{
			BoxComponent* pBoxComponent = dynamic_cast<BoxComponent*>(component);
			if (pBoxComponent == nullptr)
				continue;

			// 박스 그리는 용도면 패스
			if( pBoxComponent->GetNoCollision())
				continue;

			colliderComponents.push_back(pBoxComponent);
		}
	}

	// 충돌 테스트
	for (auto& pSourceBoxComponent : colliderComponents)
	{
		for (auto& pTargetBoxComponent : colliderComponents)
		{
			// 같으면 패스
			if (pSourceBoxComponent == pTargetBoxComponent)
				continue;

			// 같은 오브젝트면 패스
			if (pSourceBoxComponent->GetOwner() == pTargetBoxComponent->GetOwner())
				continue;

			// 충돌 안하면 패스
			if (!pSourceBoxComponent->IsCollide(pTargetBoxComponent))
				continue;

			// 게임 오브젝트에 알린다.
			pSourceBoxComponent->GetOwner()->OnCollide(pSourceBoxComponent,pTargetBoxComponent);
		}
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
		if (gameObject->IsCullObject() && !bbCamera.CheckIntersect(bbGameObject))
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
	wstring strCullCount = L"Culled Object Count : " + to_wstring(m_nCulledObjectCount);
	D2DRenderer::m_Instance->DrawText(pRenderTarget,strCullCount, D2D1::RectF(0,0,300,50), D2D1::ColorF(D2D1::ColorF::White));
}
