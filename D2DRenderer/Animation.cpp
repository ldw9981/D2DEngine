#include "pch.h"
#include "Animation.h"
#include "D2DRenderer.h"

AnimationAsset::AnimationAsset()
:m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
	int a = m_pBitmap->Release();
}

void AnimationAsset::LoadBitmap(const WCHAR* szFilePath)
{
	m_ImageFilePath = std::wstring(szFilePath);
	D2DRenderer::m_Instance->CreateD2DBitmapFromFile(szFilePath,&m_pBitmap);	
}

AnimationInstance::AnimationInstance() 
	:m_pAnimationInfo(nullptr), m_AnimationIndex(-1), m_FrameIndex(-1),m_ProgressTime(0),m_BitmapSourceRect({0.0f,0.0f,0.0f,0.0f}), m_Flip(false), m_Speed(1.0f)
{

}

AnimationInstance::~AnimationInstance()
{
	if (m_pAnimationInfo)
	{
		m_pAnimationInfo->Release();
	}
}

void AnimationInstance::SetAnimationInfo(AnimationAsset* pAnimationInfo)
{
	if (m_pAnimationInfo != nullptr)
	{
		m_pAnimationInfo->Release();
	}
	m_pAnimationInfo = pAnimationInfo;
	pAnimationInfo->AddRef();
}

void AnimationInstance::Update(float deltaTime)
{	
	assert(m_pAnimationInfo!=nullptr);
	assert(m_pAnimationInfo != nullptr);
	const std::vector<FRAME_INFO>& Frames = m_pAnimationInfo->m_Animations[m_AnimationIndex];
	size_t MaxFrameIndex = Frames.size();

	m_ProgressTime += deltaTime * m_Speed;


	while (Frames[m_FrameIndex].DelayTime < m_ProgressTime)
	{
		m_ProgressTime -= Frames[m_FrameIndex].DelayTime;
		m_FrameIndex = (m_FrameIndex + 1) % MaxFrameIndex;
	}

	m_BitmapSourceRect = m_pAnimationInfo->m_Animations[m_AnimationIndex][m_FrameIndex].Source;
}

void AnimationInstance::Render(ID2D1RenderTarget* pRenderTarget, float x, float y)
{	
	D2D1_RECT_F dest = { 0,0,m_BitmapSourceRect.right - m_BitmapSourceRect.left,m_BitmapSourceRect.bottom - m_BitmapSourceRect.top };

	if (m_Flip)
	{
		D2D1_MATRIX_3X2_F Scale(D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)));
		D2D1_MATRIX_3X2_F Translation(D2D1::Matrix3x2F::Translation(x + dest.right, y));
		
		pRenderTarget->SetTransform( Scale* Translation);
	}	
	else
	{
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
	}

	// 이미지 크기를 조정하거나 회전할 때 사용되는 알고리즘을 지정합니다.
	pRenderTarget->DrawBitmap(m_pAnimationInfo->m_pBitmap, dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_BitmapSourceRect);
}

void AnimationInstance::ChangeAnimationIndex(int index,bool Flip)
{
	assert(m_pAnimationInfo != nullptr);
	assert(m_pAnimationInfo->m_Animations.size() > index);

	m_AnimationIndex = index;
	m_FrameIndex = 0;
	m_ProgressTime = 0.0f;
	m_Flip = Flip;
}
