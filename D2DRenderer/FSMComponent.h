#pragma once
#include "Component.h"
#include "Helper.h"

class FSMState;
class FSMComponent :
    public Component
{
public:
	FSMComponent()
	:m_pCurrentState(nullptr), m_pInitialState(nullptr)
	{

	}
	virtual ~FSMComponent();
protected:

	FSMState* m_pCurrentState;  // ���� ����
	FSMState* m_pInitialState;	// �ʱ� ����

	std::map<std::wstring,FSMState*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�


	virtual void Update() override;
	void ChangeState(std::wstring stateName);
public:
	template<typename T>
	T* CreateState(std::wstring stateName)
	{
		// �̹� �ִ� ���� �̸����� Ȯ��
		auto it = m_pStates.find(stateName);
		if (it != m_pStates.end())
		{
			Log(L"%s Already Exist State", __FUNCDNAME__);
			return dynamic_cast<T*>(it->second);
		}

		// �θ�Ŭ������ FSMState���� Ȯ��
		bool bIsBase = std::is_base_of<FSMState, T>::value;
		assert(bIsBase == true);
		T* newInstance = new T();

		// FSMState�� FSMComponent�� ����
		newInstance->SetOwner(this);	
		// FSMState�� GameObject�� ����
		newInstance->SetGameObject(m_pOwner);
		// �˻� �ϰų� �ı��ڿ��� delete �ϱ����� ����
		m_pStates.insert(make_pair(stateName, newInstance));
		return newInstance;
	}
};

