#pragma once
#include "Helper.h"
#include "AnimationComponent.h"

class FSMComponent;
class FSMState;
class FSMTransition;
class FSMStateAlias;
class FSMInstance : public IAnimationNotify
{
public:
	FSMInstance(FSMComponent* pOwnerComponent)
		:m_pCurrentState(nullptr), m_pInitialState(nullptr), m_pOwnerComponent(pOwnerComponent)
	{
	
	}
	virtual ~FSMInstance();
protected:
	FSMState* m_pCurrentState;  // 현재 상태
	FSMState* m_pInitialState;	// 초기 상태
	FSMComponent* m_pOwnerComponent;	// FSMComponent

	std::map<std::wstring, FSMState*> m_pStates;	// 생성된 FSMState들을 저장하는 컨테이너

	std::vector<FSMStateAlias*> m_pStateAlias;	// 상태 별칭들을 저장하는 컨테이너
public:
	virtual void Update();
	void ChangeState(std::wstring stateName);

	void AddState(FSMState* pState);
	void AddStateAlias(FSMStateAlias* pStateAlias);

	// 애니메이션 이벤트를 받아서 현재 활성화된 State에 전달
	virtual void OnAnimationEnd(const std::wstring& AnimationName) override;
	virtual void OnAnimationNotify(const std::wstring& NotifyName) override;

};

