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

	virtual void Serialize(std::ofstream& ofstream)=0;	
	virtual void Serialize(std::ifstream& ofstream)=0;
};

