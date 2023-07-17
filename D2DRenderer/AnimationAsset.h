#pragma once

#include "ReferenceCounter.h"
#include <vector>




// �ִϸ��̼� �⺻ �������� �⺻ ����
struct FRAME_INFO
{
	D2D1_RECT_F Source;			// �̹������� �ϳ��� ����� ��� ������ �ִ���
	D2D1_VECTOR_2F Center;		// �ϳ��� FRAME���� ������� 0,0 ����  ������ ��ǥ
	FLOAT		RenderTime;		// �ϳ��� ����� �׸� �ð�

	FRAME_INFO()
	{
		Source.left = 0;
		Source.top = 0;
		Source.right = 0;
		Source.bottom = 0;
		RenderTime = 0;
		Center.x = 0;
		Center.y = 0;
	}

	FRAME_INFO(float left, float top, float right, float bottom, float centerX,float centerY, float time)
	{
		Source.left = left;
		Source.top = top;
		Source.right = right;
		Source.bottom = bottom;
		Center.x = centerX;
		Center.y = centerY;
		RenderTime = time;
	}
	FRAME_INFO(D2D1_RECT_F rect, float centerX, float centerY, float time)
	{
		Source = rect;
		Center.x = centerX;
		Center.y = centerY;
		RenderTime = time;
	}	
};

/*
	�ϳ��� ���ۿ� ���� ����
*/
struct ANIMATION_INFO
{
	std::string m_Name; // �ִϸ��̼��� �̸�	�̸����� �˻��Ͽ� ����Ѵ�.
	std::vector<FRAME_INFO> m_Frames; // �������� ����
	ANIMATION_INFO()
	:m_Name("Default")
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
	ANIMATION_INFO* GetAnimationInfo(const char* AnimationName);

	void Save(const WCHAR* szFilePath);
	bool Load(const WCHAR* szFilePath);
};