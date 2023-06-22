#pragma once
/*
	오브젝트의 모든 공통 기능을 정의하는 추상 클래스
	추후 Save/Load를 하는 Serialize을 선언할 예정
	자식 클래스는 Serialize를 구현해야 한다.
*/
class Object
{
public:
	Object()
	{

	};
	virtual ~Object()
	{

	};

	virtual bool Initialize()=0; //초기화로 오브젝트를 사용가능한지확인한다.
	virtual void Update()=0;	//오브젝트의 상태를 업데이트한다.
};

