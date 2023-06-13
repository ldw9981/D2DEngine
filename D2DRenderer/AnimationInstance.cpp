#include "pch.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"


AnimationInstance::AnimationInstance()
	:m_pAnimationAsset(nullptr), m_AnimationIndex(0), m_FrameIndex(0), m_ProgressTime(0), m_bMirror(false), m_Speed(1.0f)
{
	m_SrcRect = { 0.0f,0.0f,0.0f,0.0f };
	m_DstRect = { 0.0f,0.0f,0.0f,0.0f };
	m_Position = { 0.0f,0.0f };
	m_Transform = D2D1::Matrix3x2F::Identity();

}

AnimationInstance::~AnimationInstance()
{
	D2DRenderer::m_Instance->ReleaseAnimationAsset(m_pAnimationAsset);
}

void AnimationInstance::SetAnimationInfo(AnimationAsset* pAnimationInfo)
{
	if (m_pAnimationAsset != nullptr)
	{
		D2DRenderer::m_Instance->ReleaseAnimationAsset(m_pAnimationAsset);
	}
	m_pAnimationAsset = pAnimationInfo;
	pAnimationInfo->AddRef();
}

void AnimationInstance::Update(float deltaTime)
{
	assert(m_pAnimationAsset != nullptr);
	assert(m_pAnimationAsset != nullptr);
	const std::vector<FRAME_INFO>& Frames = m_pAnimationAsset->m_Animations[m_AnimationIndex];
	size_t MaxFrameIndex = Frames.size();

	m_ProgressTime += deltaTime * m_Speed;


	while (Frames[m_FrameIndex].RenderTime < m_ProgressTime)
	{
		m_ProgressTime -= Frames[m_FrameIndex].RenderTime;
		m_FrameIndex = (m_FrameIndex + 1) % MaxFrameIndex;
	}
	// 이지미에서의 프레임 영역
	m_SrcRect = m_pAnimationAsset->m_Animations[m_AnimationIndex][m_FrameIndex].Source;
	// 그릴 영역을 0,0,with,height으로 설정하고 실제 위치는 Transform으로 설정
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };
	if (m_bMirror)
	{
		D2D1_MATRIX_3X2_F Scale(D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)));
		D2D1_MATRIX_3X2_F Translation(D2D1::Matrix3x2F::Translation(m_Position.x + m_DstRect.right, m_Position.y));
		m_Transform = Scale * Translation;
	}
	else
	{
		m_Transform = D2D1::Matrix3x2F::Translation(m_Position.x, m_Position.y);
	}
}

void AnimationInstance::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(m_Transform);
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

