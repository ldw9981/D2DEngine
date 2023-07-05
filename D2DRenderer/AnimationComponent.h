#pragma once
#include "SceneComponent.h"
#include "RenderComponent.h"

class IAnimationNotify
{
public:
	virtual void OnAnimationEnd(const std::wstring& AnimationName) = 0;
	virtual void OnAnimationNotify(const std::wstring& NotifyName) = 0;
};


/*
	�ִϸ��̼� Instance�� �����ϴ� ������Ʈ
*/

class AnimationAsset;
struct ANIMATION_INFO;
class GameObject;
class AnimationComponent :
    public RenderComponent
{
public:
	AnimationComponent(GameObject* pOwner, const std::wstring& Name);
	virtual ~AnimationComponent();


	
public:	
	std::wstring m_strAnimationAsset;
	AnimationAsset* m_pAnimationAsset;		// �ִϸ��̼��� ���� �⺻ ������ �ڻ� (���ο� D2D1Bitmap)


	std::list<IAnimationNotify*> m_Listener;	// �ִϸ��̼� ��Ƽ����

	// ����	����
	std::vector<D2D1_RECT_F> m_AttackHitBoxes;
	// ������ ����
	std::vector<D2D1_RECT_F> m_DamgageHitBoxes;


	ANIMATION_INFO* m_pAnimationInfo;	// ���� �ִϸ��̼� ����

	size_t m_FrameIndexCurr;			// ���� ������ �ε���
	size_t m_FrameIndexPrev;		// ���� ������ �ε���
	float m_ProgressTime;			// �ִϸ��̼� ����ð�
	D2D1_RECT_F m_SrcRect;			// �ð��� ���� D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect;			// �ð��� ���� D2D1Bitmap�� Source ����		
	bool m_bMirror;					// �¿� ���� ����
	float m_Speed;					// �ִϸ��̼� �ӵ�
	bool m_Loop;
	D2D1_MATRIX_3X2_F m_RenderTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f , Matrix3x2F::Translation(m_DstRect.right,0.0f)�� �����Ѵ�.
public:

	void SetProgressTime(float val) { m_ProgressTime = val; }
	void SetSpeed(float val) { m_Speed = val; }
	void SetMirror(bool Mirror) { m_bMirror = Mirror;  }
	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

	void SetAnimation(const WCHAR* AnimationName, bool Mirror, bool Loop);
	void SetAnimationAsset(const std::wstring& strAssetKey);

	void AddListener(IAnimationNotify* pNotify);
	void RemoveListener(IAnimationNotify* pNotify);
};

