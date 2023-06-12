#include "pch.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"


AnimationInstance::AnimationInstance()
	:m_pAnimationAsset(nullptr), m_AnimationIndex(-1), m_FrameIndex(-1), m_ProgressTime(0), m_SrcRect({ 0.0f,0.0f,0.0f,0.0f }), m_Flip(false), m_Speed(1.0f)
{

}

AnimationInstance::~AnimationInstance()
{
	if (m_pAnimationAsset)
	{
		m_pAnimationAsset->Release();
	}
}

void AnimationInstance::SetAnimationInfo(AnimationAsset* pAnimationInfo)
{
	if (m_pAnimationAsset != nullptr)
	{
		m_pAnimationAsset->Release();
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
}

void AnimationInstance::Render(ID2D1RenderTarget* pRenderTarget, float x, float y)
{
	// 그릴 영역을 0,0,with,height으로 설정하고 실제 위치는 Transform으로 설정
	D2D1_RECT_F DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_Flip)
	{
		D2D1_MATRIX_3X2_F Scale(D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)));
		D2D1_MATRIX_3X2_F Translation(D2D1::Matrix3x2F::Translation(x + DstRect.right, y));
		pRenderTarget->SetTransform(Scale * Translation);
	}
	else
	{
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
	}

	// 이미지 크기를 조정하거나 회전할 때 사용되는 알고리즘을 지정합니다.
	pRenderTarget->DrawBitmap(m_pAnimationAsset->m_pBitmap, DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
}

void AnimationInstance::ChangeAnimationIndex(int index, bool Flip)
{
	assert(m_pAnimationAsset != nullptr);
	assert(m_pAnimationAsset->m_Animations.size() > index);

	m_AnimationIndex = index;
	m_FrameIndex = 0;
	m_ProgressTime = 0.0f;
	m_Flip = Flip;
}
