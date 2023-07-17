#pragma once
#include "Component.h"
#include "FiniteStateMachine.h"
/*
	컴포넌트 사용자가 CreateFiniteStateMachine호출하여 을 상속받은 클래스를 생성해야한다.
	컴포넌트는 생성된 FiniteStateMachine의 Update만 호출해준다.
*/
class FiniteStateMachine;
class GameObject;
class FSMComponent :
    public Component 
{
public:
	FSMComponent(GameObject* pOwner, const std::string& Name)
		:Component(pOwner, Name),m_pFiniteStateMachine(nullptr)
	{

	}

	virtual ~FSMComponent()
	{
		if (m_pFiniteStateMachine != nullptr)
			delete m_pFiniteStateMachine;
	}
protected:
	FiniteStateMachine* m_pFiniteStateMachine;
public:
	virtual void Update()
	{
		if (m_pFiniteStateMachine != nullptr)
			m_pFiniteStateMachine->Update();
	}

	template<typename T>
	T* CreateFiniteStateMachine()
	{
		assert(m_pFiniteStateMachine==nullptr);
		// 부모클래스가 FSMState인지 확인
		bool bIsBase = std::is_base_of<FiniteStateMachine, T>::value;
		assert(bIsBase == true);
		T* newInstance = new T(this);

		m_pFiniteStateMachine = newInstance;
		return newInstance;
	}
};

