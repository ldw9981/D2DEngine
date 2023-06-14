#pragma once
#include "FactoryResource.h"

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
	D2D1_RECT_F m_DstRect;			// �ð��� ���� D2D1Bitmap�� Source ����		
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

