#pragma once
#include "SceneComponent.h"
#include "RenderComponent.h"

class AnimationComponent;
class IAnimationNotify
{
public:
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent,const std::string& AnimationName) = 0;
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
	AnimationComponent(GameObject* pOwner, const std::string& Name);
	virtual ~AnimationComponent();


	
public:	
	std::wstring m_strAnimationAsset;
	AnimationAsset* m_pAnimationAsset;		// �ִϸ��̼��� ���� �⺻ ������ �ڻ� (���ο� D2D1Bitmap)
		

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
	
public:

	void SetProgressTime(float val) { m_ProgressTime = val; }
	void SetSpeed(float val) { m_Speed = val; }
	void SetMirror(bool Mirror) { m_bMirror = Mirror;  }
	virtual void Update(float DeltaTime) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

	void SetAnimation(const char* AnimationName, bool Mirror, bool Loop);
	void SetAnimationAsset(const std::wstring& strAssetKey);

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
};

