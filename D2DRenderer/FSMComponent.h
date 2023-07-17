#pragma once
#include "Component.h"
#include "FiniteStateMachine.h"
/*
	������Ʈ ����ڰ� CreateFiniteStateMachineȣ���Ͽ� �� ��ӹ��� Ŭ������ �����ؾ��Ѵ�.
	������Ʈ�� ������ FiniteStateMachine�� Update�� ȣ�����ش�.
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
		// �θ�Ŭ������ FSMState���� Ȯ��
		bool bIsBase = std::is_base_of<FiniteStateMachine, T>::value;
		assert(bIsBase == true);
		T* newInstance = new T(this);

		m_pFiniteStateMachine = newInstance;
		return newInstance;
	}
};

