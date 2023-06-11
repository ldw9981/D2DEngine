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
	�ִϸ��̼ǿ� ���õ� ������ �ʴ� ����
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
	�ִϸ��̼��� �ϴ� ��ü���� �ٸ� ����
	���� �ִϸ��̼�,���� ������,���� �ִϸ��̼� ����ð�,
*/
class AnimationInstance
{
public:
	AnimationInstance();
	~AnimationInstance();
protected:
	AnimationAsset* m_pAnimationInfo;			// �׸������� �⺻ ����(���ο� D2D1Bitmap)
	size_t m_AnimationIndex;
	size_t m_FrameIndex;
	float m_ProgressTime;
	D2D1_RECT_F m_BitmapSourceRect;			// �ð��� ���� D2D1Bitmap�� Source ����
	bool m_Flip;
	float m_Speed;
public:
	void SetSpeed(float val) { m_Speed = val; }
	void SetAnimationInfo(AnimationAsset* pAnimationInfo);
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget, float x, float y);
	void ChangeAnimationIndex(int index, bool Flip);
};

