#pragma once
#include "SceneComponent.h"
#include "RenderComponent.h"

/*
	애니메이션 인스턴스와 다른점은 히트박스를 가지고 있다는 점이다.
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

	// 공격	영역
	std::vector<D2D1_RECT_F> m_AttackHitBoxes;
	// 데미지 영역
	std::vector<D2D1_RECT_F> m_DamgageHitBoxes;
public:
	void SetAnimationAssetPath(const std::wstring& strAssetKey) { m_strAnimationAssetPath = strAssetKey; }
};

