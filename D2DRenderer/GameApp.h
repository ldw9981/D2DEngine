#pragma once

#define MAX_LOADSTRING 100

/*
	GameAppŬ������ ���� ������ ������ �޽��� ó�� �Ǵ� ��� ���ӿ��� ���������� ����ϴ�
	�κ��� �����ϱ����� �θ� Ŭ������ �������. 
*/
class D2DRenderer;
class GameApp
{
public:
	GameApp(HINSTANCE hInstance, int nCmdShow);
	~GameApp();

	
	static HWND m_hWnd;		//�����ʿ��ϴ� ������ ���������� ���ϱ����� ��������� �������.
	static GameApp* m_pInstance;			// �����ڿ��� �ν��Ͻ� �����͸� �����Ѵ�.
protected:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;                                // ���� �ν��Ͻ��Դϴ�.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WNDCLASSEXW m_wcex;

	int  m_nCmdShow;
	D2DRenderer* m_pD2DRenderer;
public:

	virtual bool Initialize();
	virtual void Loop();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();

	BOOL GetClientRect(LPRECT lpRect);
	int MessageBoxComError(HRESULT hr);

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
};

