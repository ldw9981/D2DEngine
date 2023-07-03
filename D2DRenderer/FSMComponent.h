#pragma once
#include "Component.h"


class FSMInstance;
class FSMComponent :
    public Component 
{
public:
	FSMComponent()	
	:m_pFSMInstance(nullptr)
	{
		
	}

	virtual ~FSMComponent();
protected:
	FSMInstance* m_pFSMInstance;
public:
	virtual void Update() override;

	template<typename T>
	T* CreateInstance()
	{
		// �θ�Ŭ������ FSMState���� Ȯ��
		bool bIsBase = std::is_base_of<FSMInstance, T>::value;
		assert(bIsBase == true);
		T* newInstance = new T(this);

		m_pFSMInstance = newInstance;
		return newInstance;
	}
};

