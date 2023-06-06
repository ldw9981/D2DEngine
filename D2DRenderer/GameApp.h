#pragma once

#define MAX_LOADSTRING 100



class GameApp
{
public:
	GameApp(HINSTANCE hInstance, int nCmdShow);
	~GameApp();
protected:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;                                // 현재 인스턴스입니다.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	WNDCLASSEXW m_wcex;
	HWND m_hWnd;
	int  m_nCmdShow;
public:
	static GameApp* m_pInstance;
	virtual bool Initialize();
	virtual void Loop();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();


	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
};

