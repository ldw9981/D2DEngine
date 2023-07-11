#include "pch.h"
#include "BoxComponent.h"
#include "D2DRenderer.h"
#include "Helper.h"

BoxComponent::BoxComponent(GameObject* pOwner, const std::wstring& Name)
	:ColliderComponent(pOwner, Name),m_Rect({0})
{
	m_ColliderType = ColliderType::Box;
	m_CollisionType = CollisionType::Block;
}


BoxComponent::~BoxComponent()
{

}


void BoxComponent::SetExtend(float x, float y)
{
	m_Rect.right = x;
	m_Rect.bottom = y;
	m_Rect.left = -x;
	m_Rect.top = -y;

	m_Collider.m_Extend.x = x;
	m_Collider.m_Extend.y = y;

	m_BoundingBox.m_Extend.x = x;
	m_BoundingBox.m_Extend.y = y;
}

void BoxComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_Instance->GetBrush();
	pBrush->SetColor(GetColor());	
	
	// 월드->카메라->스크린 좌표계로 변환한다. 
	// m_ScreenTransform 의 ScaleY -1 이므로 거꾸로 그려진다. 
	// m_RenderTransform에서 제일처음 변환에 ScaleY -1을 곱해준다.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawRectangle(m_Rect,pBrush);	

	DrawDebugWorldTransform(pRenderTarget);
}

void BoxComponent::Update()
{
	__super::Update();
	m_Collider.m_Center = GetWorldLocation();
	m_BoundingBox.m_Center = GetWorldLocation();
}

bool BoxComponent::IsCollide(ColliderComponent* pOtherComponent)
{
	if (pOtherComponent->GetColliderType() == ColliderType::Box)
	{
		BoxComponent* pOtherBoxComponent = static_cast<BoxComponent*>(pOtherComponent);		
		if (!m_Collider.CheckIntersect(pOtherBoxComponent->m_Collider))
			return false;

		return true;
	}
	return false;
}
