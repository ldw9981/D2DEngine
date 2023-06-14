#pragma once

#include "FactoryResource.h"
#include <vector>



// 애니메이션 기본 프레임의 기본 정보
struct FRAME_INFO
{
	D2D1_RECT_F Source;
	float		RenderTime;

	FRAME_INFO(float x, float y, float with, float height, float time)
	{
		Source.left = x;
		Source.top = y;
		Source.right = x + with;
		Source.bottom = y + height;
		RenderTime = time;
	}
	FRAME_INFO(D2D1_RECT_F rect, float time)
	{
		Source = rect;
		RenderTime = time;
	}
};

/*
	애니메이션에 필요한 변하지않는 데이터 자산
*/
class AnimationAsset : public FactoryResource
{
	// 파괴는 Release로 , 생성은 D2DRenderer가 하게한다.
protected:
	AnimationAsset();
	virtual ~AnimationAsset();
	friend class D2DRenderer;			
public:
	ID2D1Bitmap* m_pBitmap;
	std::wstring m_BitmapFilePath;

	std::vector<std::vector<FRAME_INFO>> m_Animations;

	void Build();
	void SetBitmapFilePath(const WCHAR* szFilePath);
};