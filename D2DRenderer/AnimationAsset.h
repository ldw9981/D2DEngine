#pragma once

#include "ReferenceCounter.h"
#include <vector>



// �ִϸ��̼� �⺻ �������� �⺻ ����
struct FRAME_INFO
{
	D2D1_RECT_F Source;			// �̹������� �ϳ��� ����� ��� ������ �ִ���
	float		RenderTime;		// �ϳ��� ����� �׸� �ð�

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
	�ϳ��� ���ۿ� ���� ����
*/
struct ANIMATION_INFO
{
	std::wstring m_Name; // �ִϸ��̼��� �̸�	�̸����� �˻��Ͽ� ����Ѵ�.
	std::vector<FRAME_INFO> m_Frames; // �������� ����
	ANIMATION_INFO()
	:m_Name(L"Default")
	{
		
	}
};

/*
	�ִϸ��̼ǿ� �ʿ��� �������ʴ� ������ �ڻ�
	���� ĳ���Ͱ� �����ص� �б� ���� ������ �ϳ��� �ʿ��ϴ�.
*/
class AnimationAsset : public ReferenceCounter
{
	// �ı��� Release�� , ������ D2DRenderer�� �ϰ��Ѵ�.
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