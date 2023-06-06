#include "pch.h"
#include "GameApp.h"

GameApp* GameApp::m_pInstance = nullptr;



LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return  GameApp::m_pInstance->WndProc(hWnd,message,wParam,lParam);
}

GameApp::GameApp(HINSTANCE hInstance, int nCmdShow)
	:m_nCmdShow(nCmdShow), m_hInstance(hInstance), m_szWindowClass(L"DefaultWindowCalss"), m_szTitle(L"GameApp")
{
	GameApp::m_pInstance = this;
	m_wcex.hInstance = hInstance;
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = DefaultWndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wcex.lpszClassName = m_szWindowClass;
}

GameApp::~GameApp()
{

}

// ������ ������ ���� ���� �ٸ��� �����Ƿ� ���,����,���̱⸸ �Ѵ�.
bool GameApp::Initialize()
{
	// ���
	RegisterClassExW(&m_wcex);

	//����
	m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
		100, 100,	// ���� ��ġ
		800, 600,	// ����,����
		nullptr, nullptr, m_hInstance, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	// ������ ���̱�
	ShowWindow(m_hWnd, m_nCmdShow);
	UpdateWindow(m_hWnd);
	return true;
}

void GameApp::Loop()
{
	// �⺻ �޽��� �����Դϴ�:
	/*
	// GetMessage�� �޼����� �߻��Ҷ����� �������� �����Ƿ� �������� ȭ�鰻��,������Ʈ�� ���� ���Ӱ��� �����ʴ�.
	while (GetMessage(&m_msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(m_msg.hwnd, m_hAccelTable, &m_msg))
		{
			TranslateMessage(&m_msg);  // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&m_msg);
		}
	}
	*/

	// PeekMessage �޼����� ������ true,������ false
	while (TRUE)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT)
				break;

			//������ �޽��� ó�� 
			TranslateMessage(&m_msg); // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&m_msg);
		}
		else
		{
			Update();
			Render();
		}
	}


	//return (int)m_msg.wParam;
}

void GameApp::Update()
{

}

void GameApp::Render()
{

}

void GameApp::Finalize()
{

}




//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK GameApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// �����̹Ƿ� �޴��¾��ش�.
		/*
		case WM_COMMAND:
		{

			int wmId = LOWORD(wParam);
			// �޴� ������ ���� �м��մϴ�:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}

		}
		break;
		*/
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}