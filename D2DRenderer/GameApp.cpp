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

// 윈도우 정보는 게임 마다 다를수 있으므로 등록,생성,보이기만 한다.
bool GameApp::Initialize(UINT Width, UINT Height)
{
	m_ClientSize.width = Width;
	m_ClientSize.height = Height;

	// 등록
	RegisterClassExW(&m_wcex);

	// 원하는 크기가 조정되어 리턴
	RECT rcClient = { 0, 0, (LONG)m_ClientSize.width, (LONG)m_ClientSize.height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	//생성
	m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
		100, 100,	// 시작 위치
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		nullptr, nullptr, m_hInstance, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	// 윈도우 보이기
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
	// PeekMessage 메세지가 있으면 true,없으면 false
	while (TRUE)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT)
				break;

			//윈도우 메시지 처리 
			TranslateMessage(&m_msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
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
	// 어떤 게임이라도 시간업데이트는 한다.
	m_previousTime = m_currentTime;
	m_currentTime = (float)GetTickCount64() / 1000.0f;
	m_deltaTime = m_currentTime - m_previousTime;
	CalculateFrameStats();
	m_World.Update();
}

void GameApp::CalculateFrameStats()
{
	//해당 코드는 초당 프레임을 계산하고, 1프레임 렌더시 걸리는 시간의 평균을 계산한다.
	//해당 수치들은 창의 제목표시줄에 추가된다.

	static int frameCnt = -1;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if(frameCnt==0)
		return;

	timeElapsed+= m_deltaTime;

	//1초동안의 프레임 시간의 평균을 계산합니다.
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

		//다음 계산을위해 리셋
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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK GameApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// 게임이므로 메뉴는없앤다.
		/*
		case WM_COMMAND:
		{

			int wmId = LOWORD(wParam);
			// 메뉴 선택을 구문 분석합니다:
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
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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