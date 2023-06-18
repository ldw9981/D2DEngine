#pragma once
#include "SceneComponent.h"
#include "RenderComponent.h"

class AnimationInstance;
class AnimationAsset;
class AnimationComponent :
    public RenderComponent
{
public:
	AnimationComponent();
	virtual ~AnimationComponent();

	virtual bool Init() override;
	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	
public:	
	std::wstring m_strAnimationAsset;
	AnimationInstance* m_pAnimationInstance;
	AnimationAsset* m_pAnimationAsset;

	std::vector<D2D1_RECT_F> m_vecHitBox;
	std::vector<D2D1_RECT_F> m_vecAttackBox;
};

