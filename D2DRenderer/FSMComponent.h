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

	FSMState* m_pCurrentState;  // 현재 상태
	FSMState* m_pInitialState;	// 초기 상태

	std::map<std::wstring,FSMState*> m_pStates;	// 생성된 FSMState들을 저장하는 컨테이너


	virtual void Update() override;
	void ChangeState(std::wstring stateName);
public:
	template<typename T>
	T* CreateState(std::wstring stateName)
	{
		// 이미 있는 상태 이름인지 확인
		auto it = m_pStates.find(stateName);
		if (it != m_pStates.end())
		{
			Log(L"%s Already Exist State", __FUNCDNAME__);
			return dynamic_cast<T*>(it->second);
		}

		// 부모클래스가 FSMState인지 확인
		bool bIsBase = std::is_base_of<FSMState, T>::value;
		assert(bIsBase == true);
		T* newInstance = new T();

		// FSMState에 FSMComponent를 설정
		newInstance->SetOwner(this);	
		// FSMState에 GameObject를 설정
		newInstance->SetGameObject(m_pOwner);
		// 검색 하거나 파괴자에서 delete 하기위해 저장
		m_pStates.insert(make_pair(stateName, newInstance));
		return newInstance;
	}
};

