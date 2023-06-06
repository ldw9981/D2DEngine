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
	HINSTANCE m_hInstance;                                // ���� �ν��Ͻ��Դϴ�.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
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

