// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DemoApp.h"
#include "../D2DRenderer/D2DRenderer.h"
#include <d2d1.h>

// D2DEngine프로젝트에서 기본 윈도우 생성,루프 기능 클래스로 래핑한 를 구현

DemoApp::DemoApp(HINSTANCE hInstance)
// GameApp클래스는 기본생성자가 없기때문에 자식클래스 DemoApp이 GameApp을 어떻게 생성자 호출할지 알려줘야한다.
:GameApp::GameApp(hInstance)
{ 
    // 윈도우 클래스 준비하는 작업을 다른 함수로 만들고 싶지 않아 생성자에서 한다.
    // 실행파일에 합쳐진 데이터 영역에서 DemoApp에 관한 아이콘이나 문자를 가져와 윈도우 클래스 정보를 준비한다.

	LoadStringW(m_hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadStringW(m_hInstance, IDC_DEMOAPP, m_szWindowClass, MAX_LOADSTRING);
	m_wcex.hInstance = m_hInstance;
	m_wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_DEMOAPP));
	//m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOAPP);                  //게임이므로 메뉴는 없앤다
	m_wcex.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_SMALL));
    m_hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_DEMOAPP));
}

DemoApp::~DemoApp()
{
    OutputDebugString(L"DemoApp::~DemoApp()\n");
}


bool DemoApp::Initialize()
{
    bool bRet = GameApp::Initialize();
	if (!bRet)
	    return false;

    HRESULT hr;

    hr = m_pD2DRenderer->CreateD2DBitmapFromFile(L"../Resource/atk_1.png", &m_pD2DBitmap1);
    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderer->CreateD2DBitmapFromFile(L"../Resource/atk_1.png", &m_pD2DBitmap2);
    }

    m_pAnimationInfo = m_pD2DRenderer->CreateAnimationInfo(L"Test");
    m_pAnimationInfo->LoadBitmap(L"../Resource/run.png");
    std::vector<FRAME_INFO> Frames;
    Frames.push_back(FRAME_INFO(28, 36, 103, 84, 0.1f));
	Frames.push_back(FRAME_INFO(148, 36, 86, 84, 0.1f));
	Frames.push_back(FRAME_INFO(255, 34, 87, 86, 0.1f));
    Frames.push_back(FRAME_INFO(363, 32, 76, 88, 0.1f));
    Frames.push_back(FRAME_INFO(458, 31,  91, 89, 0.1f));
    Frames.push_back(FRAME_INFO(567, 40, 103, 80, 0.1f));
    Frames.push_back(FRAME_INFO(686, 32,  85, 88, 0.1f));
    Frames.push_back(FRAME_INFO(792, 32,  86, 88, 0.1f));
    Frames.push_back(FRAME_INFO(899, 31, 76, 89,  0.1f));
    Frames.push_back(FRAME_INFO(993, 33,  92, 87, 0.1f));    
    m_pAnimationInfo->m_Animations.push_back(Frames);

    m_pAnimationInstance = new AnimationInstance;
    m_pAnimationInstance->SetAnimationInfo(m_pAnimationInfo);
    m_pAnimationInstance->ChangeAnimationIndex(0,true);

    if (FAILED(hr))
    {
        MessageBoxComError(hr);
        return false;
    }	
    return true;
}

void DemoApp::Finalize()
{
    delete m_pAnimationInstance;
    if (m_pAnimationInfo != nullptr)
    {
        m_pAnimationInfo->Release();
    }
        


    if(m_pD2DBitmap1!=nullptr)
        m_pD2DBitmap1->Release();

	
    if (m_pD2DBitmap2 != nullptr)
        m_pD2DBitmap2->Release();

    GameApp::Finalize();
}

void DemoApp::Render()
{


    D2DRenderer::m_pRenderTarget->BeginDraw();
    D2DRenderer::m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
 

    D2DRenderer::m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    D2DRenderer::m_pRenderTarget->DrawBitmap(m_pD2DBitmap1);
	
      /*
	  STDMETHOD_(void, DrawBitmap)(
		_In_ ID2D1Bitmap *bitmap,
		_In_opt_ CONST D2D1_RECT_F *destinationRectangle = NULL,
		FLOAT opacity = 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		_In_opt_ CONST D2D1_RECT_F *sourceRectangle = NULL
		) PURE;
     */

    D2D1_RECT_F rectSrc = { 0.0f,0.0f,100.0f,100.0f};
    D2D1_RECT_F rectDst = { 0.0f,0.0f,100.0f,100.0f };

    
    D2DRenderer::m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,30));
    D2DRenderer::m_pRenderTarget->DrawBitmap(m_pD2DBitmap2, rectSrc,1.0f,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rectSrc);


    m_pAnimationInstance->Render(D2DRenderer::m_pRenderTarget,100,50);

    m_pD2DRenderer->EndDraw();
}

void DemoApp::Update()
{
    GameApp::Update();

    m_pAnimationInstance->Update(m_deltaTime);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    
    //GameApp App(hInstance, nCmdShow);   // 기본클래스도 윈도우 생성,메시지 루프 잘작동한다.
    DemoApp App(hInstance);  // 생성자에서 아이콘,윈도우 이름만 바꾼다

    App.Initialize();
    App.Loop();
    App.Finalize();
}




