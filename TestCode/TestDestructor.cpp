// TestCode.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
#include "TestCode.h"
#include <iostream>
#include "ClassOwner.h"
#include "ClassChild.h"
#include "ClassParent.h"

int main()
{

	// 부모클래스와 자식클래스의 파괴자가 모두 문제없이 호출됨 	
	//	ClassChild B;  


	// 부모클래스와 자식클래스의 파괴자가 모두 문제없이 호출됨 
	//	ClassChild* p = new ClassChild;
	//	delete p;


	// 부모클래스의 파괴자가 virtual 키워드를 사용하지않으면 ClassParent의 파괴자만 호출됨
	// vitual 키워드를 사용하면 가상함수 테이블에 있는 자식클래스의 파괴자호출하고 이후 부모클래스의 파괴자까지 호출됨 
	// 예를들면 보통 일괄처리위해 WorldClass 의 멤버로 list<GameObject*> m_GameObjects;  이런식으로 자식클래스를 부모타입의 포인터로 보관함

	ClassParent* p = new ClassChild;
	p->Function();
	delete p;

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
*/