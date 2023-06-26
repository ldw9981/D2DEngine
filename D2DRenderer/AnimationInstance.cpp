#include "pch.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "AnimationComponent.h"
#include "D2DRenderer.h"
#include "GameApp.h"
#include "RendererHelper.h"


AnimationInstance::AnimationInstance()
	:m_pAnimationAsset(nullptr), m_AnimationIndex(0), m_FrameIndex(0), m_ProgressTime(0), m_bMirror(false), m_Speed(1.0f)
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



	D2D1_VECTOR_2F Location;
	m_pAnimationComponent->GetWorldLocation(&Location);

	if (m_bMirror)
	{	
		m_RenderTransform = D2D1::Matrix3x2F::Scale(-1.0f,-1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(m_DstRect.right,0.0f);
	}
	else
	{		
		m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(0.0f, 0.0f);
	}

	
}

void AnimationInstance::Render(ID2D1RenderTarget* pRenderTarget)
{
	// 월드->카메라->스크린 좌표계로 변환한다. Screen 의 y스케일이 -1 이므로 거꾸로 그려진다. 제일처음 변환에 -1을 곱해준다.
	D2D_MATRIX_3X2_F Transform = m_RenderTransform * m_pAnimationComponent->GetWorldTransform() * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(m_pAnimationAsset->m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

void AnimationInstance::SetAnimationIndex(size_t index, bool Mirror)
{
	assert(m_pAnimationAsset != nullptr);
	assert(m_pAnimationAsset->m_Animations.size() > index);

	m_AnimationIndex = index;
	m_FrameIndex = 0;
	m_ProgressTime = 0.0f;
	m_bMirror = Mirror;
}

