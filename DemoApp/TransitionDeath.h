#pragma once
#include "../D2DRenderer/FSMTransition.h"


class FSMInstanceTest2;
class TransitionDeath :
    public FSMTransition
{
public:
	TransitionDeath(FSMInstance* pOwner) 
	: FSMTransition(pOwner) 
	{
		m_pFSMIntance = (FSMInstanceTest2*)pOwner;
	}

	~TransitionDeath()
	{

	}

	FSMInstanceTest2* m_pFSMIntance = nullptr;

	virtual bool CheckCondition() override;
};

