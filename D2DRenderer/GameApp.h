#pragma once

#define MAX_LOADSTRING 100

/*
	GameAppŬ������ ���� ������ ������ �޽��� ó�� �Ǵ� ��� ���ӿ��� ���������� ����ϴ�
	�κ��� �����ϱ����� �θ� Ŭ������ �������. 
*/
#include "../D2DRenderer/D2DRenderer.h"
#include "../D2DRenderer/World.h"

class D2DRenderer;
class GameApp
{
public:
	GameApp(HINSTANCE hInstance);
	virtual ~GameApp();

	
	static HWND m_hWnd;		//�����ʿ��ϴ� ������ ���������� ���ϱ����� ��������� �������.
	static GameApp* m_pInstance;			// �����ڿ��� �ν��Ͻ� �����͸� �����Ѵ�.
	static float m_deltaTime;
protected:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;                                // ���� �ν��Ͻ��Դϴ�.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WNDCLASSEXW m_wcex;

	int  m_nCmdShow;
	D2DRenderer m_D2DRenderer;
	D2D_SIZE_U m_ClientSize;

	float m_previousTime;
	float m_currentTime;
	
	World m_World;
public:

	virtual bool Initialize();
	virtual void Loop();
	virtual void Update();
	virtual void Render();

	const D2D_SIZE_U& GetClientSize() { return m_ClientSize; 	}
	BOOL GetClientRect(LPRECT lpRect);
	int MessageBoxComError(HRESULT hr);
	void CalculateFrameStats();

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
};

