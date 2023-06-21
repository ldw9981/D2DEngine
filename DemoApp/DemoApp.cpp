// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DemoApp.h"
#include "../D2DRenderer/D2DRenderer.h"
#include "../D2DRenderer/AnimationAsset.h"
#include "DemoObject.h"
#include <d2d1.h>
#include <memory>

// D2DEngine프로젝트에서 기본 윈도우 생성,루프 기능 클래스로 래핑한 를 구현
// GameApp클래스는 기본생성자가 없기때문에 자식클래스 DemoApp이 GameApp을 어떻게 생성자 호출할지 알려줘야한다.
DemoApp::DemoApp(HINSTANCE hInstance)
    :GameApp::GameApp(hInstance), 
        m_pAnimationAsset(nullptr),
        m_pDemoObject(nullptr)
{ 

	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

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

// DemoApp의 파괴자 -> 멤버변수로 사용한 클래스의 파괴자 -> GameApp의 파괴자  순으로 호출된다.
DemoApp::~DemoApp()
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());
	
	if (m_pAnimationAsset != nullptr)
	{
        m_D2DRenderer.ReleaseAnimationAsset(m_pAnimationAsset);
	}



   
}


bool DemoApp::Initialize()
{
    bool bRet = GameApp::Initialize();
	if (!bRet)
	    return false;

    // 애니메이션 정보는 파일에서 읽어야 하나 여기서는 하드코딩으로 만들어서 사용한다.
    ANIMATION_INFO Animation;
    m_pAnimationAsset = m_D2DRenderer.CreateAnimationAsset(L"Test");
    m_pAnimationAsset->SetBitmapFilePath(L"../Resource/run.png");
    m_pAnimationAsset->Build();
    Animation.m_Frames.clear();
    Animation.m_Frames.push_back(FRAME_INFO( 28, 36, 103, 84, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(148, 36,  86, 84, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(255, 34,  87, 86, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(363, 32,  76, 88, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(458, 31,  91, 89, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(567, 40, 103, 80, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(686, 32,  85, 88, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(792, 32,  86, 88, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(899, 31,  76, 89, 0.1f));
    Animation.m_Frames.push_back(FRAME_INFO(993, 33,  92, 87, 0.1f));
    m_pAnimationAsset->m_Animations.push_back(Animation);
    	
	// DemoObject를 생성하고 초기화한다.
    // 월드의 CreateGameObject()함수를 호출하면 GameObject를 생성하고 월드에 등록한다.
    m_pDemoObject = m_World.CreateGameObject<DemoObject>();
    m_pDemoObject->Initialize();
    // RootSceneComponent의 Location을 중앙위치로 설정
    m_pDemoObject->SetLocation((float)m_ClientSize.width / 2, (float)m_ClientSize.height / 2);   
    return true;
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
}




