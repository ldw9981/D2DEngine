#pragma once
#include "ReferenceCounter.h"
#include "Object.h"

class D2DRenderer;
class AnimationAsset;
class AnimationComponent;
/*
	애니메이션을 하는 객체마다 다른 정보
	현재 애니메이션,현재 프레임,현재 애니메이션 진행시간,
*/
class AnimationInstance : public Object
{
public:
	AnimationInstance();
	virtual ~AnimationInstance();

protected:
	AnimationComponent* m_pAnimationComponent;
	AnimationAsset* m_pAnimationAsset;		// 애니메이션을 위한 기본 데이터 자산 (내부에 D2D1Bitmap)
	size_t m_AnimationIndex;		// 현재 애니메이션 인덱스
	size_t m_FrameIndex;			// 현재 프레임 인덱스
	float m_ProgressTime;			// 애니메이션 진행시간
	D2D1_RECT_F m_SrcRect;			// 시간에 따른 D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect;			// 시간에 따른 D2D1Bitmap의 Source 영역		
	bool m_bMirror;
	float m_Speed;
	D2D1_MATRIX_3X2_F m_RenderTransform;
public:
	virtual bool Initialize() override;
	void SetProgressTime(float val) { m_ProgressTime = val; }
	void SetSpeed(float val) { m_Speed = val; }
	void SetAnimationInfo(AnimationAsset* pAnimationInfo);
	void Update();
	void Render(ID2D1RenderTarget* pRenderTarget);
	void SetAnimationIndex(size_t index, bool Flip);

	void SetAnimationComponent(AnimationComponent* pAnimationComponent) { m_pAnimationComponent = pAnimationComponent; }
};

