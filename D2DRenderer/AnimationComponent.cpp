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
	// ���� �ִϸ��̼� ���� ����
	if(m_pAnimationAsset)
	{
		D2DRenderer::m_Instance->ReleaseSharedAnimationAsset(m_pAnimationAsset);
		m_pAnimationAsset = nullptr;
	}
}



void AnimationComponent::Update()
{
	__super::Update();	
	// asset�� ������ ���
	assert(m_pAnimationAsset != nullptr);

	// ������ �ִϸ��̼��� ������ ����
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
	
	// ������ ���������� ��ȣ�� ���Ҷ� ���ѹ� �̺�Ʈ ȣ��
	if (m_FrameIndexCurr!= m_FrameIndexPrev && m_FrameIndexCurr == (MaxFrameCount - 1)) 
	{
		GetOwner()->OnAnimationEnd(this, m_Name);
	}

	// �����̿����� ������ ����
	m_SrcRect = Frame.Source;
	// �׸� ������ 0,0,with,height���� �����ϰ� ���� ��ġ�� Transform���� ����
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };
	
		

	//x�� �������� �¿� ���� , Y�� -1�������� ����Ƽ ��ũ����ǥ�踦 �� ���� �̸� ���Ϲ��� ,  Translation�� ����� �̹����� ���� ����
	if (m_bMirror)
	{			
		m_RenderTransform = D2D1::Matrix3x2F::Scale(-1.0f, -1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0, 0)) * D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
	
	/*
		Todo: �ִϸ��̼��� ����� ���庯ȯ���� ��Ʈ�ڽ��� ��ġ�� ������Ʈ �������
	*/

}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	DrawDebugWorldTransform(pRenderTarget);

	// ����->ī�޶�->��ũ�� ��ǥ��� ��ȯ�Ѵ�. 
	// m_ScreenTransform �� ScaleY -1 �̹Ƿ� �Ųٷ� �׷�����. 
	// m_RenderTransform���� ����ó�� ��ȯ�� ScaleY -1�� �����ش�.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;

	// ������ �ִϸ��̼� ������ �ȱ׸�
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