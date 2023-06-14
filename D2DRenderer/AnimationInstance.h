#pragma once
#include "FactoryResource.h"

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
	D2D1_RECT_F m_DstRect;			// 시간에 따른 D2D1Bitmap의 Source 영역		
	bool m_bMirror;
	float m_Speed;

	D2D1_MATRIX_3X2_F m_Transform;
	D2D1_VECTOR_2F m_Position;
public:
	void SetProgressTime(float val) { m_ProgressTime = val; }
	void SetSpeed(float val) { m_Speed = val; }
	void SetAnimationInfo(AnimationAsset* pAnimationInfo);
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void SetAnimationIndex(size_t index, bool Flip);
	void SetPosition(float x,float y) { m_Position = {x,y}; }
};

