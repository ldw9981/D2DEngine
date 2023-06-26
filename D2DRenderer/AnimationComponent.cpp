#include "pch.h"
#include "AnimationComponent.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "RendererHelper.h"

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
	__super::Update();

	if (m_pAnimationInstance)
	{
		// �ִϸ��̼� ����� ���� ��Ʈ�ڽ� ������ ���Ѵ�.
		m_pAnimationInstance->Update();
	}

	/*
		Todo: �ִϸ��̼��� ����� ���庯ȯ���� ��Ʈ�ڽ��� ��ġ�� ������Ʈ �������
	*/

}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	// ����->ī�޶�->��ũ�� ��ǥ��� ��ȯ�Ѵ�. Screen �� y�������� -1 �̹Ƿ� �Ųٷ� �׷�����. ����ó�� ��ȯ�� -1�� �����ش�.
	D2D1_MATRIX_3X2_F Transform = Matrix3x2F::Scale(1.0f, -1.0f) * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	
	pRenderTarget->SetTransform(Transform);	
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);

	if (m_pAnimationInstance)
	{
		m_pAnimationInstance->Render(pRenderTarget);
	}
}
