#pragma once
#include "ReferenceCounter.h"

class D2DRenderer;
class AnimationAsset;

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
	AnimationAsset* m_pAnimationAsset;		// �ִϸ��̼��� ���� �⺻ ������ �ڻ� (���ο� D2D1Bitmap)
	size_t m_AnimationIndex;		// ���� �ִϸ��̼� �ε���
	size_t m_FrameIndex;			// ���� ������ �ε���
	float m_ProgressTime;			// �ִϸ��̼� ����ð�
	D2D1_RECT_F m_SrcRect;			// �ð��� ���� D2D1Bitmap�� Source ����		
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

