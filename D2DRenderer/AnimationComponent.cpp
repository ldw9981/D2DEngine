#include "pch.h"
#include "AnimationComponent.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "GameApp.h"

AnimationComponent::AnimationComponent()
{
	m_pAnimationAsset = nullptr;
	m_FrameIndex = 0;
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

	assert(m_pAnimationAsset != nullptr);

	if (m_pAnimationInfo == nullptr)
		return;

	const FRAME_INFO& Frame = m_pAnimationInfo->m_Frames[m_FrameIndex];
	size_t MaxFrameIndex = m_pAnimationInfo->m_Frames.size();

	m_ProgressTime += GameApp::m_deltaTime * m_Speed;


	while (Frame.RenderTime < m_ProgressTime)
	{	
		for (auto it : m_Listener)
		{
			it->OnAnimationEnd();
		}
				
		m_ProgressTime -= Frame.RenderTime;
		m_FrameIndex = (m_FrameIndex + 1) % MaxFrameIndex;
	}
	// 이지미에서의 프레임 영역
	m_SrcRect = Frame.Source;
	// 그릴 영역을 0,0,with,height으로 설정하고 실제 위치는 Transform으로 설정
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };



	D2D1_VECTOR_2F Location = GetWorldLocation();

	if (m_bMirror)
	{
		m_RenderTransform = D2D1::Matrix3x2F::Scale(-1.0f, -1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(m_DstRect.right, 0.0f);
	}
	else
	{
		m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(0.0f, 0.0f);
	}
	
	/*
		Todo: 애니메이션의 결과와 월드변환으로 히트박스의 위치를 업데이트 해줘야함
	*/

}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	// 월드->카메라->스크린 좌표계로 변환한다. Screen 의 y스케일이 -1 이므로 거꾸로 그려진다. 제일처음 변환에 -1을 곱해준다.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	
	pRenderTarget->SetTransform(Transform);	
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);

	if (m_pAnimationInfo == nullptr)
		return;

	pRenderTarget->DrawBitmap(m_pAnimationAsset->m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}


void AnimationComponent::SetAnimation(const WCHAR* AnimationName, bool Mirror, bool Loop)
{
	assert(m_pAnimationAsset != nullptr);

	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimationInfo(AnimationName);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_bMirror = Mirror;
	m_FrameIndex = 0;
	m_ProgressTime = 0.0f;
	m_Loop = Loop;
}

void AnimationComponent::SetAnimationAsset(const std::wstring& strAssetKey)
{
	assert(strAssetKey.empty()==false);
	m_strAnimationAsset = strAssetKey;
	m_pAnimationAsset = D2DRenderer::m_Instance->CreateSharedAnimationAsset(strAssetKey);
}

void AnimationComponent::AddListener(IAnimationNotify* pNotify)
{
	m_Listener.push_back(pNotify);
}

void AnimationComponent::RemoveListener(IAnimationNotify* pNotify)
{
	m_Listener.remove(pNotify);
}

