#pragma once

#define MAX_LOADSTRING 100

/*
	GameApp클래스를 만든 이유는 윈도우 메시지 처리 또는 모든 게임에서 공통적으로 사용하는
	부분을 구현하기위해 부모 클래스로 만들었다. 
*/
#include "../D2DRenderer/D2DRenderer.h"

class D2DRenderer;
class GameApp
{
public:
	GameApp(HINSTANCE hInstance);
	virtual ~GameApp();

	
	static HWND m_hWnd;		//자주필요하니 포인터 간접접근을 피하기위해 정적멤버로 만들었다.
	static GameApp* m_pInstance;			// 생성자에서 인스턴스 포인터를 보관한다.
	
protected:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;                                // 현재 인스턴스입니다.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	WNDCLASSEXW m_wcex;

	int  m_nCmdShow;
	D2DRenderer m_pD2DRenderer;

	int m_nWidth;
	int m_nHeight;
	float m_previousTime;
	float m_currentTime;
	float m_deltaTime;
public:

	virtual bool Initialize();
	virtual void Loop();
	virtual void Update();
	virtual void Render();


	BOOL GetClientRect(LPRECT lpRect);
	int MessageBoxComError(HRESULT hr);
	void CalculateFrameStats();

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
};

