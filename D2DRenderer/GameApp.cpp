#include "pch.h"
#include "GameApp.h"
#include "D2DRenderer.h"
#include "Helper.h"

GameApp* GameApp::m_pInstance = nullptr;

float GameApp::m_deltaTime = 0.0f;

HWND GameApp::m_hWnd;


LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return  GameApp::m_pInstance->WndProc(hWnd,message,wParam,lParam);
}

GameApp::GameApp(HINSTANCE hInstance)
	:m_hInstance(hInstance), m_szWindowClass(L"DefaultWindowCalss"), m_szTitle(L"GameApp"),m_ClientSize({1024,768})
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

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
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());
	
}

// ������ ������ ���� ���� �ٸ��� �����Ƿ� ���,����,���̱⸸ �Ѵ�.
bool GameApp::Initialize(UINT Width, UINT Height)
{
	m_ClientSize.width = Width;
	m_ClientSize.height = Height;

	// ���
	RegisterClassExW(&m_wcex);

	// ���ϴ� ũ�Ⱑ �����Ǿ� ����
	RECT rcClient = { 0, 0, (LONG)m_ClientSize.width, (LONG)m_ClientSize.height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	//����
	m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
		100, 100,	// ���� ��ġ
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		nullptr, nullptr, m_hInstance, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	// ������ ���̱�
	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);

	m_currentTime = m_previousTime = (float)GetTickCount64() / 1000.0f;


	HRESULT hr = m_D2DRenderer.Initialize();
	if (FAILED(hr))
	{
		_com_error err(hr);
		LOG_ERROR(L"%s",err.ErrorMessage());
	}

	return true;
}

void GameApp::Loop()
{
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
	// � �����̶� �ð�������Ʈ�� �Ѵ�.
	m_previousTime = m_currentTime;
	m_currentTime = (float)GetTickCount64() / 1000.0f;
	m_deltaTime = m_currentTime - m_previousTime;
	CalculateFrameStats();
	m_World.Update();
}

void GameApp::CalculateFrameStats()
{
	//�ش� �ڵ�� �ʴ� �������� ����ϰ�, 1������ ������ �ɸ��� �ð��� ����� ����Ѵ�.
	//�ش� ��ġ���� â�� ����ǥ���ٿ� �߰��ȴ�.

	static int frameCnt = -1;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if(frameCnt==0)
		return;

	timeElapsed+= m_deltaTime;

	//1�ʵ����� ������ �ð��� ����� ����մϴ�.
	if ( timeElapsed >= 1.0f)
	{
		float fps = (float)frameCnt;  //Frame Per Second
		float spf = 1000.0f / fps;   // MilliSecond Per Frame

		std::wstring windowText;
		windowText.append(m_szTitle);
		windowText.append(L"  FPS: ");
		windowText.append(std::to_wstring(fps));
		windowText.append(L"  SPF: ");
		windowText.append(std::to_wstring(spf));
		windowText.append(L" Used VRAM: ");
		windowText.append(std::to_wstring(D2DRenderer::m_Instance->GetUsedVRAM()));
		windowText.append(L"MB");

		SetWindowText(m_hWnd, windowText.c_str());

		//���� ��������� ����
		frameCnt = 0;
		timeElapsed -= 1.0f;
	}
}

void GameApp::Render()
{
	D2DRenderer::m_pRenderTarget->BeginDraw();
	D2DRenderer::m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	m_World.Render(D2DRenderer::m_pRenderTarget);
	m_D2DRenderer.EndDraw();
}



BOOL GameApp::GetClientRect(LPRECT lpRect)
{
	return ::GetClientRect(m_hWnd, lpRect);
}

int GameApp::MessageBoxComError(HRESULT hr)
{
	_com_error err(hr);
	return ::MessageBox(m_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
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