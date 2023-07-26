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
	애니메이션 Instance를 관리하는 컴포넌트
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
	AnimationAsset* m_pAnimationAsset;		// 애니메이션을 위한 기본 데이터 자산 (내부에 D2D1Bitmap)
		

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

