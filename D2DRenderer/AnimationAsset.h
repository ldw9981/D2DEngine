#pragma once

#include "FactoryResource.h"
#include <vector>



// �ִϸ��̼� �⺻ �������� �⺻ ����
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
	�ִϸ��̼ǿ� �ʿ��� �������ʴ� ������ �ڻ�
*/
class AnimationAsset : public FactoryResource
{
	// �ı��� Release�� , ������ D2DRenderer�� �ϰ��Ѵ�.
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