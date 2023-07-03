#pragma once
#include "../D2DRenderer/FSMInstance.h"
#include "../D2DRenderer/FSMState.h"
#include "../D2DRenderer/FSMTransition.h"
#include "StateIdle.h"
#include "TransitionDeath.h"

#include "../D2DRenderer/FSMStateAlias.h"

class FSMInstanceTest2 :
    public FSMInstance
{
public:
	FSMInstanceTest2(FSMComponent* pOwner)
	: FSMInstance(pOwner),
		m_StateIdle(this),
		m_TransitionToIdle(this),
		m_StateAliasDeath(this,L"StateAliasDeath")
	{
		AddState(&m_StateIdle);
		AddStateAlias(&m_StateAliasDeath);
	}
	virtual ~FSMInstanceTest2()
	{
	
	}

	StateIdle m_StateIdle;
	TransitionDeath m_TransitionToIdle;
	FSMStateAlias m_StateAliasDeath;
	
};

