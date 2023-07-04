#pragma once
#include "../D2DRenderer/FSMTransition.h"


class FSMCharacter;
class TransitionDeath :
    public FSMTransition
{
public:
	TransitionDeath(FiniteStateMachine* pOwner)
	: FSMTransition(pOwner) 
	{
		m_pFSMIntance = (FSMCharacter*)pOwner;
	}

	~TransitionDeath()
	{

	}

	FSMCharacter* m_pFSMIntance = nullptr;

	virtual bool CheckCondition() override;
};

