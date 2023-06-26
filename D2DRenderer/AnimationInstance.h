#pragma once
#include "ReferenceCounter.h"
#include "Object.h"

class D2DRenderer;
class AnimationAsset;
class AnimationComponent;
/*
	�ִϸ��̼��� �ϴ� ��ü���� �ٸ� ����
	���� �ִϸ��̼�,���� ������,���� �ִϸ��̼� ����ð�,
*/
class AnimationInstance : public Object
{
public:
	AnimationInstance();
	virtual ~AnimationInstance();

protected:
	AnimationComponent* m_pAnimationComponent;
	AnimationAsset* m_pAnimationAsset;		// �ִϸ��̼��� ���� �⺻ ������ �ڻ� (���ο� D2D1Bitmap)
	size_t m_AnimationIndex;		// ���� �ִϸ��̼� �ε���
	size_t m_FrameIndex;			// ���� ������ �ε���
	float m_ProgressTime;			// �ִϸ��̼� ����ð�
	D2D1_RECT_F m_SrcRect;			// �ð��� ���� D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect;			// �ð��� ���� D2D1Bitmap�� Source ����		
	bool m_bMirror;					// �¿� ���� ����
	float m_Speed;					// �ִϸ��̼� �ӵ�
	D2D1_MATRIX_3X2_F m_RenderTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f , Matrix3x2F::Translation(m_DstRect.right,0.0f)�� �����Ѵ�.
public:
	virtual bool Initialize() override;
	void SetProgressTime(float val) { m_ProgressTime = val; }
	void SetSpeed(float val) { m_Speed = val; }
	void SetAnimationInfo(AnimationAsset* pAnimationInfo);
	void Update();
	void Render(ID2D1RenderTarget* pRenderTarget);
	void SetAnimationIndex(size_t index, bool Mirror);

	// ����� ������ �Ǵ� AnimationComponent�� �����Ѵ�.
	void SetAnimationComponent(AnimationComponent* pAnimationComponent) { m_pAnimationComponent = pAnimationComponent; }
};

