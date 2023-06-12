#pragma once
#include "ReferenceCounter.h"

class D2DRenderer;
class AnimationAsset;

/*
	애니메이션을 하는 객체마다 다른 정보
	현재 애니메이션,현재 프레임,현재 애니메이션 진행시간,
*/
class AnimationInstance
{
public:
	AnimationInstance();
	~AnimationInstance();
		
protected:
	AnimationAsset* m_pAnimationAsset;		// 애니메이션을 위한 기본 데이터 자산 (내부에 D2D1Bitmap)
	size_t m_AnimationIndex;		// 현재 애니메이션 인덱스
	size_t m_FrameIndex;			// 현재 프레임 인덱스
	float m_ProgressTime;			// 애니메이션 진행시간
	D2D1_RECT_F m_SrcRect;			// 시간에 따른 D2D1Bitmap의 Source 영역		
	bool m_Flip;
	float m_Speed;
public:
	void SetProgressTime(float val) { m_ProgressTime = val; }
	void SetSpeed(float val) { m_Speed = val; }
	void SetAnimationInfo(AnimationAsset* pAnimationInfo);
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget, float x, float y);
	void ChangeAnimationIndex(int index, bool Flip);
};

