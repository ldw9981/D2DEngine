#pragma once
#include "SceneComponent.h"
#include "RenderComponent.h"

/*
	�ִϸ��̼� �ν��Ͻ��� �ٸ����� ��Ʈ�ڽ��� ������ �ִٴ� ���̴�.
*/

class AnimationInstance;
class AnimationAsset;
class AnimationComponent :
    public RenderComponent
{
public:
	AnimationComponent();
	virtual ~AnimationComponent();

	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	
public:	
	std::wstring m_strAnimationAssetPath;
	AnimationInstance* m_pAnimationInstance;
	AnimationAsset* m_pAnimationAsset;

	// ����	����
	std::vector<D2D1_RECT_F> m_AttackHitBoxes;
	// ������ ����
	std::vector<D2D1_RECT_F> m_DamgageHitBoxes;
public:
	void SetAnimationAssetPath(const std::wstring& strAssetKey) { m_strAnimationAssetPath = strAssetKey; }
};

