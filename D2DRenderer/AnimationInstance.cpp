#include "pch.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "AnimationComponent.h"
#include "D2DRenderer.h"
#include "GameApp.h"


AnimationInstance::AnimationInstance()
	:m_pAnimationAsset(nullptr), m_AnimationIndex(0), m_FrameIndex(0), m_ProgressTime(0), m_bMirror(true), m_Speed(1.0f)
{
	m_pAnimationComponent=nullptr;
	m_SrcRect = { 0.0f,0.0f,0.0f,0.0f };
	m_DstRect = { 0.0f,0.0f,0.0f,0.0f };
	m_RenderTransform = D2D1::Matrix3x2F::Identity();

}

AnimationInstance::~AnimationInstance()
{
	if (m_pAnimationAsset)
	{
		D2DRenderer::m_Instance->ReleaseAnimationAsset(m_pAnimationAsset);
	}

}

bool AnimationInstance::Initialize()
{
	assert(m_pAnimationAsset!=nullptr);
	assert(m_pAnimationAsset->m_Animations.empty() == false);
	assert(m_pAnimationAsset->m_Animations[0].m_Frames.empty() == false);
	assert(m_pAnimationComponent != nullptr);
	

	return true;
}

void AnimationInstance::SetAnimationInfo(AnimationAsset* pAnimationInfo)
{
	m_pAnimationAsset = pAnimationInfo;
	pAnimationInfo->AddRef();
}

void AnimationInstance::Update()
{
	assert(m_pAnimationAsset != nullptr);

	const ANIMATION_INFO& Animation = m_pAnimationAsset->m_Animations[m_AnimationIndex];
	const FRAME_INFO& Frame = Animation.m_Frames[m_FrameIndex];
	size_t MaxFrameIndex = Animation.m_Frames.size();

	m_ProgressTime += GameApp::m_deltaTime * m_Speed;


	while (Frame.RenderTime < m_ProgressTime)
	{
		m_ProgressTime -= Frame.RenderTime;
		m_FrameIndex = (m_FrameIndex + 1) % MaxFrameIndex;
	}
	// 이지미에서의 프레임 영역
	m_SrcRect = Frame.Source;
	// 그릴 영역을 0,0,with,height으로 설정하고 실제 위치는 Transform으로 설정
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	
	if (m_bMirror)
	{	
		m_RenderTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(m_DstRect.right, 0.0f);
	}
	else
	{		
		m_RenderTransform = D2D1::Matrix3x2F::Identity();
	}

	if (m_pAnimationComponent)
	{
		m_RenderTransform = m_RenderTransform * m_pAnimationComponent->GetWorldTransform();
	}
}

void AnimationInstance::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(m_RenderTransform);
	pRenderTarget->DrawBitmap(m_pAnimationAsset->m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
}

void AnimationInstance::SetAnimationIndex(size_t index, bool bMirror)
{
	assert(m_pAnimationAsset != nullptr);
	assert(m_pAnimationAsset->m_Animations.size() > index);

	m_AnimationIndex = index;
	m_FrameIndex = 0;
	m_ProgressTime = 0.0f;
	m_bMirror = bMirror;
}

