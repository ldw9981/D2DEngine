// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DemoApp.h"
#include "../D2DRenderer/D2DRenderer.h"
#include "../D2DRenderer/AnimationAsset.h"
#include "../D2DRenderer/Camera.h"
#include "DemoObject.h"
#include "PlatformObject.h"
#include "PlayerCharacter.h"

// D2DEngine프로젝트에서 기본 윈도우 생성,루프 기능 클래스로 래핑한 를 구현
// GameApp클래스는 기본생성자가 없기때문에 자식클래스 DemoApp이 GameApp을 어떻게 생성자 호출할지 알려줘야한다.
DemoApp::DemoApp(HINSTANCE hInstance)
    :GameApp::GameApp(hInstance), 
        m_pAnimationAsset(nullptr),
    m_pTest1Object{0,}
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
        m_D2DRenderer.ReleaseSharedAnimationAsset(m_pAnimationAsset);
	}
}


bool DemoApp::Initialize(UINT Width, UINT Height)
{
    bool bRet = GameApp::Initialize(Width,Height);
	if (!bRet)
	    return false;
    	
	// DemoObject를 생성하고 초기화한다.
    // 월드의 CreateGameObject()함수를 호출하면 GameObject를 생성하고 월드에 등록한다.
    for (int i=0;i< MAX_DEMO_OBJECT;i++)
    {
        m_pTest1Object[i] = m_World.CreateGameObject<PlatformObject>();       
		// RootSceneComponent의 Location을 중앙위치로 설정
        m_pTest1Object[i]->SetWorldLocation(mathHelper::Vector2F(500 + (float) i * 100 ,40));
    }

    GameObject* pGameObject = m_World.CreateGameObject<PlayerCharacter>();
    pGameObject->SetWorldLocation(mathHelper::Vector2F(0, 0));
    CameraComponent* pCameraComponent = (CameraComponent*)pGameObject->GetComponent("CameraComponent");
    m_World.SetCamera(pCameraComponent);    
    
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

    App.Initialize(1024,768);
    App.Loop();
}




