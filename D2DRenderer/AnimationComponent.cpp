#include "pch.h"
#include "AnimationComponent.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "GameApp.h"
#include "GameObject.h"
#include "RenderComponent.h"

AnimationComponent::AnimationComponent(GameObject* pOwner, const std::string& Name)
	:RenderComponent(pOwner, Name)
{
	m_pAnimationAsset = nullptr;
	m_FrameIndexCurr = 0;
	m_ProgressTime = 0;
	m_bMirror = false;
	m_Speed=1.0f;
	m_Loop = false;
	m_pAnimationInfo = nullptr;
	m_SrcRect = { 0.0f,0.0f,0.0f,0.0f };
	m_DstRect = { 0.0f,0.0f,0.0f,0.0f };
	m_RenderTransform = D2D1::Matrix3x2F::Identity();
}

AnimationComponent::~AnimationComponent()
{
	// 공유 애니메이션 정보 해제
	if(m_pAnimationAsset)
	{
		D2DRenderer::m_Instance->ReleaseSharedAnimationAsset(m_pAnimationAsset);
		m_pAnimationAsset = nullptr;
	}
}



void AnimationComponent::Update()
{
	__super::Update();	
	// asset이 없으면 경고
	assert(m_pAnimationAsset != nullptr);

	// 지정한 애니메이션이 없으면 리턴
	if (m_pAnimationInfo == nullptr)
		return;

	const FRAME_INFO& Frame = m_pAnimationInfo->m_Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->m_Frames.size();

	m_ProgressTime += GameApp::m_deltaTime * m_Speed;

	m_FrameIndexPrev = m_FrameIndexCurr;
	while (Frame.RenderTime < m_ProgressTime)
	{			
		m_ProgressTime -= Frame.RenderTime;

		if (m_Loop)
		{
			m_FrameIndexCurr = (m_FrameIndexCurr + 1) % MaxFrameCount;
		}
		else
		{ 
			m_FrameIndexCurr = min(m_FrameIndexCurr + 1, MaxFrameCount - 1);
		}
	}
	
	// 마지막 프레임으로 번호가 변할때 단한번 이벤트 호출
	if (m_FrameIndexCurr!= m_FrameIndexPrev && m_FrameIndexCurr == (MaxFrameCount - 1)) 
	{
		GetOwner()->OnAnimationEnd(this, m_Name);
	}

	// 이지미에서의 프레임 영역
	m_SrcRect = Frame.Source;
	// 그릴 영역을 0,0,with,height으로 설정하고 실제 위치는 Transform으로 설정
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };
	
		

	//x축 스케일은 좌우 반전 , Y축 -1스케일은 유니티 스크린좌표계를 를 위해 미리 상하반전 ,  Translation은 출력할 이미지의 원점 정보
	if (m_bMirror)
	{			
		m_RenderTransform = D2D1::Matrix3x2F::Scale(-1.0f, -1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
	
	/*
		Todo: 애니메이션의 결과와 월드변환으로 히트박스의 위치를 업데이트 해줘야함
	*/

}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	DrawDebugWorldTransform(pRenderTarget);

	// 월드->카메라->스크린 좌표계로 변환한다. 
	// m_ScreenTransform 의 ScaleY -1 이므로 거꾸로 그려진다. 
	// m_RenderTransform에서 제일처음 변환에 ScaleY -1을 곱해준다.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;

	// 지정한 애니메이션 없으면 안그림
	if (m_pAnimationInfo == nullptr)
		return;

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(m_pAnimationAsset->m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}


void AnimationComponent::SetAnimation(const char* AnimationName, bool Mirror, bool Loop)
{
	assert(m_pAnimationAsset != nullptr);

	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimationInfo(AnimationName);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_bMirror = Mirror;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_ProgressTime = 0.0f;
	m_Loop = Loop;
}

void AnimationComponent::SetAnimationAsset(const std::wstring& strAssetKey)
{
	assert(strAssetKey.empty()==false);
	m_strAnimationAsset = strAssetKey;
	m_pAnimationAsset = D2DRenderer::m_Instance->CreateSharedAnimationAsset(strAssetKey);
}

void AnimationComponent::SerializeOut(nlohmann::ordered_json& object)
{
	RenderComponent::SerializeOut(object);
	object["m_strAnimationAsset"] = D2DHelper::WStringToString(m_strAnimationAsset);
}