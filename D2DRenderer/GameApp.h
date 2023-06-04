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
	//static GameApp* m_pInstance;
	void Initialize();
	void Loop();
	virtual void Update();
	virtual void Render();
	void Finalize();


	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

