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
	FSMState* m_pCurrentState;  // ���� ����
	FSMState* m_pInitialState;	// �ʱ� ����
	FSMComponent* m_pOwnerComponent;	// FSMComponent

	std::map<std::wstring, FSMState*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�

	std::vector<FSMStateAlias*> m_pStateAlias;	// ���� ��Ī���� �����ϴ� �����̳�
public:
	virtual void Update();
	void ChangeState(std::wstring stateName);

	void AddState(FSMState* pState);
	void AddStateAlias(FSMStateAlias* pStateAlias);

	// �ִϸ��̼� �̺�Ʈ�� �޾Ƽ� ���� Ȱ��ȭ�� State�� ����
	virtual void OnAnimationEnd(const std::wstring& AnimationName) override;
	virtual void OnAnimationNotify(const std::wstring& NotifyName) override;

};

