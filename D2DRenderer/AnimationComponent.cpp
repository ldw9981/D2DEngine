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

bool AnimationComponent::Init()
{
	m_pAnimationInstance = new AnimationInstance();
	m_pAnimationInstance->SetAnimationComponent(this);
	if (!m_strAnimationAsset.empty())
	{
		m_pAnimationAsset = D2DRenderer::m_Instance->CreateAnimationAsset(m_strAnimationAsset);
		m_pAnimationInstance->SetAnimationInfo(m_pAnimationAsset);
	}
	return m_pAnimationInstance->Init();
}

void AnimationComponent::Update()
{
	SceneComponent::Update();
	if (m_pAnimationInstance)
	{
		m_pAnimationInstance->Update();
	}
}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (m_pAnimationInstance)
	{
		m_pAnimationInstance->Render(pRenderTarget);
	}
}
