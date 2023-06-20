#include "pch.h"
#include "AnimationComponent.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"

AnimationComponent::AnimationComponent()
{
	m_pAnimationInstance = nullptr;
	m_pAnimationAsset = nullptr;
}
AnimationComponent::~AnimationComponent()
{
	if(m_pAnimationAsset)
	{
		D2DRenderer::m_Instance->ReleaseAnimationAsset(m_pAnimationAsset);
		m_pAnimationAsset = nullptr;
	}

	if (m_pAnimationInstance)
	{
		delete m_pAnimationInstance;
		m_pAnimationInstance = nullptr;
	}
}

bool AnimationComponent::Initialize()
{
	m_pAnimationInstance = new AnimationInstance();
	m_pAnimationInstance->SetAnimationComponent(this);
	if (!m_strAnimationAssetPath.empty())
	{
		m_pAnimationAsset = D2DRenderer::m_Instance->CreateAnimationAsset(m_strAnimationAssetPath);
		m_pAnimationInstance->SetAnimationInfo(m_pAnimationAsset);
	}
	return m_pAnimationInstance->Initialize();
}

void AnimationComponent::Update()
{
	UpdateTrasnform();

	if (m_pAnimationInstance)
	{
		// 애니메이션 결과에 따라 히트박스 정보가 변한다.
		m_pAnimationInstance->Update();
	}

	/*
		Todo: 애니메이션의 결과와 월드변환으로 히트박스의 위치를 업데이트 해줘야함
	*/


	for (auto& pChild : m_Children)
	{
		pChild->Update();
	}
}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (m_pAnimationInstance)
	{
		m_pAnimationInstance->Render(pRenderTarget);
	}
}
