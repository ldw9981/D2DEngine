#pragma once
#include "ReferenceCounter.h"
#include <vector>

// 애니메이션 기본 프레임의 기본 정보
struct FRAME_INFO
{
	D2D1_RECT_F Source;
	float		DelayTime;

	FRAME_INFO(float x, float y, float with, float height, float delay)
	{
		Source.left = x;
		Source.top = y;
		Source.right = x + with;
		Source.bottom = y+ height;
		DelayTime = delay;
	}
	FRAME_INFO(D2D1_RECT_F rect, float delay)
	{
		Source= rect;
		DelayTime = delay;
	}
};

/*
	애니메이션에 관련된 변하지 않는 정보
*/
class AnimationAsset: public ReferenceCounter
{
public:
	AnimationAsset();
protected:
	virtual ~AnimationAsset();
public:
	ID2D1Bitmap* m_pBitmap;
	std::wstring m_ImageFilePath;
	std::vector<std::vector<FRAME_INFO>> m_Animations;
	
	void LoadBitmap(const WCHAR* szFilePath);
};

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
	AnimationAsset* m_pAnimationInfo;			// 그리기위한 기본 정보(내부에 D2D1Bitmap)
	size_t m_AnimationIndex;
	size_t m_FrameIndex;
	float m_ProgressTime;
	D2D1_RECT_F m_BitmapSourceRect;			// 시간에 따른 D2D1Bitmap의 Source 영역
	bool m_Flip;
	float m_Speed;
public:
	void SetSpeed(float val) { m_Speed = val; }
	void SetAnimationInfo(AnimationAsset* pAnimationInfo);
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget, float x, float y);
	void ChangeAnimationIndex(int index, bool Flip);
};

