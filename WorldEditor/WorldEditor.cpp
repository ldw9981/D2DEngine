﻿
// WorldEditor.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "WorldEditor.h"
#include "MainFrm.h"

#include "WorldEditorDoc.h"
#include "WorldEditorView.h"
#include "../D2DRenderer/Factory.h"
#include "../D2DRenderer/InputManager.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWorldEditorApp

BEGIN_MESSAGE_MAP(CWorldEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CWorldEditorApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CWorldEditorApp 생성

CWorldEditorApp::CWorldEditorApp() noexcept
:m_PlayWorld("PlayWorld")
{
	m_bHiColorIcons = TRUE;
	m_pCurrWorld = nullptr;
	m_bPlayMode = false;
	m_nAppLook = 0;
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 애플리케이션을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 애플리케이션 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("WorldEditor.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CWorldEditorApp 개체입니다.

CWorldEditorApp theApp;


// CWorldEditorApp 초기화

BOOL CWorldEditorApp::InitInstance()
{
	// 애플리케이션 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 애플리케이션의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWorldEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CWorldEditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DDE Execute 열기를 활성화합니다.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	//  SDI 응용 프로그램에서는 ProcessShellCommand 후에 이러한 호출이 발생해야 합니다.
	// 끌어서 놓기에 대한 열기를 활성화합니다.
	m_pMainWnd->DragAcceptFiles();


	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	m_Renderer.Initialize(pMainFrame->GetActiveView()->GetSafeHwnd());

	// 팩토리 테스트
	auto& result  = Factory::GetRegistry();
	auto it = result.find("Effect");
	return TRUE;
}

int CWorldEditorApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CWorldEditorApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_SIZE()
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.


void CWorldEditorApp::SetMode(bool PlayMode)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CWorldEditorDoc* pDoc = (CWorldEditorDoc*)pMainFrame->GetActiveDocument();

	if (PlayMode)
	{		
		if (!m_bPlayMode)
		{
			pDoc->m_EditWorld.OnEndPlay();
		}		
		m_bPlayMode = true;
		// Todo: 플레이모드일때는  pDoc->m_EditWorld의 내용을 복사해서 m_PlayWorld에 넣어줘야함
		pDoc->m_EditWorld.Save(L"../Resource/Temp.WorldAsset");
		m_PlayWorld.Clear();
		m_PlayWorld.Load(L"../Resource/Temp.WorldAsset");		
		m_PlayWorld.OnBeginPlay();
		m_pCurrWorld = &m_PlayWorld;
	}
	else
	{		
		if (m_bPlayMode)
			m_PlayWorld.OnEndPlay();

		m_bPlayMode = false;
		pDoc->m_EditWorld.OnBeginPlay();
		// 에디트 모드일때는 기본 카메라로 설정한다.
		pDoc->m_EditWorld.UpdateReferenceCameraComponent(-1);
				

		m_pCurrWorld = &pDoc->m_EditWorld;
	}
}

void CWorldEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CWorldEditorApp 사용자 지정 로드/저장 방법

void CWorldEditorApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CWorldEditorApp::LoadCustomState()
{
}

void CWorldEditorApp::SaveCustomState()
{
}

void CWorldEditorApp::Update()
{
	m_Timer.Tick();
	CalculateFrameStats();
	if (m_pCurrWorld != nullptr)
	{
		m_pCurrWorld->Update(m_Timer.DeltaTime());		
	}

}

void CWorldEditorApp::Render()
{
	m_Renderer.m_pRenderTarget->BeginDraw();
	m_Renderer.m_pRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f));
	
	// PlayWorld 또는 Doc의 EditWorld 가 될수 있다.
	if (m_pCurrWorld != nullptr)
	{		
		m_pCurrWorld->Render(m_Renderer.m_pRenderTarget);
	}
	m_Renderer.m_pRenderTarget->EndDraw();
}

void CWorldEditorApp::CalculateFrameStats()
{
	//해당 코드는 초당 프레임을 계산하고, 1프레임 렌더시 걸리는 시간의 평균을 계산한다.
	//해당 수치들은 창의 제목표시줄에 추가된다.

	static int frameCnt = -1;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if (frameCnt == 0)
		return;

	timeElapsed += m_Timer.DeltaTime();

	//1초동안의 프레임 시간의 평균을 계산합니다.
	if (timeElapsed >= 1.0f)
	{
		float fps = (float)frameCnt;  //Frame Per Second
		float spf = 1000.0f / fps;   // MilliSecond Per Frame
		/*
		std::wstring windowText;
	//	windowText.append(m_szTitle);
		windowText.append(L"  FPS: ");
		windowText.append(std::to_wstring(fps));
		windowText.append(L"  SPF: ");
		windowText.append(std::to_wstring(spf));
		windowText.append(L" Used VRAM: ");
		windowText.append(std::to_wstring(D2DRenderer::m_Instance->GetUsedVRAM()));
		windowText.append(L"MB");

		::SetWindowText(m_pMainWnd->GetSafeHwnd(), windowText.c_str());
		*/

		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->UpdateStatusBar(fps,spf, D2DRenderer::m_Instance->GetUsedVRAM());

		//다음 계산을위해 리셋
		frameCnt = 0;
		timeElapsed -= 1.0f;
	}
}


// CWorldEditorApp 메시지 처리기





BOOL CWorldEditorApp::OnIdle(LONG lCount)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Update();
	Render();
	return TRUE;//CWinAppEx::OnIdle(lCount);
}


CDocument* CWorldEditorApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CWinAppEx::OpenDocumentFile(lpszFileName);
}
