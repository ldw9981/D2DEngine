#pragma once

#define MAX_LOADSTRING 100

/*
	GameApp클래스를 만든 이유는 윈도우 메시지 처리 또는 모든 게임에서 공통적으로 사용하는
	부분을 구현하기위해 부모 클래스로 만들었다. 
	게임오브젝트를 생성하고 파괴하는 월드를 하나 갖는다.
*/
#include "../D2DRenderer/D2DRenderer.h"
#include "../D2DRenderer/World.h"
#include "../D2DRenderer/TimeSystem.h"
class D2DRenderer;
class GameApp
{
public:
	GameApp(HINSTANCE hInstance);
	virtual ~GameApp();

	
	static HWND m_hWnd;		//자주필요하니 포인터 간접접근을 피하기위해 정적멤버로 만들었다.
	static GameApp* m_pInstance;			// 생성자에서 인스턴스 포인터를 보관한다.
	
	GameTimer m_Timer;
public:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;                                // 현재 인스턴스입니다.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	WNDCLASSEXW m_wcex;

	int  m_nCmdShow;
	D2DRenderer m_D2DRenderer;
	D2D_SIZE_U m_ClientSize;

	float m_previousTime;
	float m_currentTime;

	World* m_pCurrentWorld;
public:

	virtual bool Initialize(UINT Width, UINT Height);
	virtual void Loop();
	virtual void Update();
	virtual void Render();

	const D2D_SIZE_U& GetClientSize() { return m_ClientSize; 	}
	BOOL GetClientRect(LPRECT lpRect);
	int MessageBoxComError(HRESULT hr);
	void CalculateFrameStats();

	void ChangeWorld(World* pWorld);

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
};

