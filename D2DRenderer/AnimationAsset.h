#pragma once

#include "ReferenceCounter.h"
#include <vector>



// 애니메이션 기본 프레임의 기본 정보
struct FRAME_INFO
{
	D2D1_RECT_F Source;			// 이미지에서 하나의 장면이 어느 영역에 있는지
	float		RenderTime;		// 하나의 장면을 그릴 시간

	FRAME_INFO()
	{
		Source.left = 0;
		Source.top = 0;
		Source.right = 0;
		Source.bottom = 0;
		RenderTime = 0;
	}

	FRAME_INFO(float left, float top, float right, float bottom, float time)
	{
		Source.left = left;
		Source.top = top;
		Source.right = right;
		Source.bottom = bottom;
		RenderTime = time;
	}
	FRAME_INFO(D2D1_RECT_F rect, float time)
	{
		Source = rect;
		RenderTime = time;
	}
};

/*
	하나의 동작에 대한 정보
*/
struct ANIMATION_INFO
{
	std::wstring m_Name; // 애니메이션의 이름	이름으로 검색하여 재생한다.
	std::vector<FRAME_INFO> m_Frames; // 프레임의 모음
	ANIMATION_INFO()
	:m_Name(L"Default")
	{
		
	}
};

/*
	애니메이션에 필요한 변하지않는 데이터 자산
	여러 캐릭터가 등장해도 읽기 전용 정보는 하나만 필요하다.
*/
class AnimationAsset : public ReferenceCounter
{
	// 파괴는 Release로 , 생성은 D2DRenderer가 하게한다.
protected:
	AnimationAsset();
	virtual ~AnimationAsset();
	friend class D2DRenderer;			
public:
	ID2D1Bitmap* m_pBitmap;
	std::wstring m_BitmapFilePath;

	std::vector<ANIMATION_INFO> m_Animations;

	void SetD2DBitmap(const WCHAR* szFilePath);
	ANIMATION_INFO* GetAnimationInfo(const WCHAR* AnimationName);
};