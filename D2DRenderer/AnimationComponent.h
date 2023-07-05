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
	애니메이션 Instance를 관리하는 컴포넌트
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
	AnimationAsset* m_pAnimationAsset;		// 애니메이션을 위한 기본 데이터 자산 (내부에 D2D1Bitmap)


	std::list<IAnimationNotify*> m_Listener;	// 애니메이션 노티파이

	// 공격	영역
	std::vector<D2D1_RECT_F> m_AttackHitBoxes;
	// 데미지 영역
	std::vector<D2D1_RECT_F> m_DamgageHitBoxes;


	ANIMATION_INFO* m_pAnimationInfo;	// 현재 애니메이션 정보

	size_t m_FrameIndexCurr;			// 현재 프레임 인덱스
	size_t m_FrameIndexPrev;		// 현재 프레임 인덱스
	float m_ProgressTime;			// 애니메이션 진행시간
	D2D1_RECT_F m_SrcRect;			// 시간에 따른 D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect;			// 시간에 따른 D2D1Bitmap의 Source 영역		
	bool m_bMirror;					// 좌우 반전 여부
	float m_Speed;					// 애니메이션 속도
	bool m_Loop;
	D2D1_MATRIX_3X2_F m_RenderTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f , Matrix3x2F::Translation(m_DstRect.right,0.0f)을 적용한다.
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

