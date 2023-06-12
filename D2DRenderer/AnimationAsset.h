#pragma once

#include "ReferenceCounter.h"
#include <vector>

// �ִϸ��̼� �⺻ �������� �⺻ ����
struct FRAME_INFO
{
	D2D1_RECT_F Source;
	float		DelayTime;

	FRAME_INFO(float x, float y, float with, float height, float delay)
	{
		Source.left = x;
		Source.top = y;
		Source.right = x + with;
		Source.bottom = y + height;
		DelayTime = delay;
	}
	FRAME_INFO(D2D1_RECT_F rect, float delay)
	{
		Source = rect;
		DelayTime = delay;
	}
};

/*
	�ִϸ��̼ǿ� �ʿ��� �������ʴ� ������ �ڻ�
*/
class AnimationAsset : public ReferenceCounter
{
public:
	AnimationAsset();
protected:
	virtual ~AnimationAsset();
public:
	ID2D1Bitmap* m_pBitmap;
	std::wstring m_BitmapFilePath;
	std::vector<std::vector<FRAME_INFO>> m_Animations;

	void Build();
	void SetBitmapFilePath(const WCHAR* szFilePath);
};