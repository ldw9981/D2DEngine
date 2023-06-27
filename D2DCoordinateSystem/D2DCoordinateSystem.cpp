// D2DDrawBitmap.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "D2DCoordinateSystem.h"
#include <d2d1.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1_1helper.h>
#include <string>
#include <dwrite.h>


#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")

#define MAX_LOADSTRING 100

using namespace D2D1;
using namespace std;

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

D2D_MATRIX_3X2_F g_matRender = Matrix3x2F::Identity(); // 렌더링 변환을 위한 행렬   
D2D_MATRIX_3X2_F g_matWorld = Matrix3x2F::Identity(); // 월드 좌표계 변환을 위한 행렬

D2D1_SIZE_U g_ScreenSize;
float g_locCameraX = 0;
float g_locCameraY = 0;
D2D_MATRIX_3X2_F g_matCamera = Matrix3x2F::Identity(); // 카메라 좌표계 변환을 위한 행렬
D2D_MATRIX_3X2_F g_matScreen = Matrix3x2F::Identity(); //왼쪽하단이 0,0인 스크린 좌표계 변환을 위한 행렬 

//  D2D 개체 인터페이스 포인터 변수
ID2D1Factory* g_pD2DFactory;
ID2D1HwndRenderTarget* g_pRenderTarget;

// D2D1비트맵 생성을 위한 이미지 처리 인터페이스
IWICImagingFactory* g_pWICFactory;
ID2D1Bitmap* g_pD2DBitmap = nullptr;

// DWrite
IDWriteFactory* g_pDWriteFactory;
IDWriteTextFormat* g_pDWriteTextFormat;

ID2D1SolidColorBrush* g_pBrush; // 브러시 개체 인터페이스 포인터 변수

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{
    HRESULT hr;
    // Create a decoder
    IWICBitmapDecoder* pDecoder = NULL;
    IWICFormatConverter* pConverter = NULL;

    hr = g_pWICFactory->CreateDecoderFromFilename(
        szFilePath,                      // Image to be decoded
        NULL,                            // Do not prefer a particular vendor
        GENERIC_READ,                    // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
        &pDecoder                        // Pointer to the decoder
    );

    // Retrieve the first frame of the image from the decoder
    IWICBitmapFrameDecode* pFrame = NULL;
    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    //Step 3: Format convert the frame to 32bppPBGRA
    if (SUCCEEDED(hr))
    {
        hr = g_pWICFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pFrame,                          // Input bitmap to convert
            GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
            WICBitmapDitherTypeNone,         // Specified dither pattern
            NULL,                            // Specify a particular palette 
            0.f,                             // Alpha threshold
            WICBitmapPaletteTypeCustom       // Palette translation type
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = g_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
    }


    // 파일을 사용할때마다 다시 만든다.
    if (pConverter)
        pConverter->Release();

    if (pDecoder)
        pDecoder->Release();

    if (pFrame)
        pFrame->Release();

    return hr;
}

void PrintMatrix(const wchar_t* str,D2D_MATRIX_3X2_F& mat,float left,float top)
{
	WCHAR buffer[256]={0};
	swprintf_s(buffer, L"%.2f, %.2f\n%.2f, %.2f\n%.2f, %.2f\n",
		mat._11, mat._12, mat._21, mat._22, mat._31, mat._32);
	OutputDebugString(buffer);

    Matrix3x2F matRender = Matrix3x2F::Identity();    
    g_pRenderTarget->SetTransform(matRender);

    g_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
    g_pRenderTarget->FillRectangle(RectF(left, top, left + 100, top+150), g_pBrush);

    g_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
    g_pRenderTarget->DrawTextW(str, wcslen(str), g_pDWriteTextFormat, RectF(left, top, left+300,top+300), g_pBrush);
    g_pRenderTarget->DrawTextW(buffer,wcslen(buffer),g_pDWriteTextFormat,RectF(left,top+60, left + 300, top+60 + 300),g_pBrush);

}

BOOL InitDirect2D()
{
    WCHAR buffer[MAX_PATH];
    // Get the current working directory
    DWORD result = GetCurrentDirectory(MAX_PATH, buffer);
    OutputDebugString(buffer);

    HRESULT hr = S_OK;
    // COM 사용 시작
    hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        /*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
            이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
            DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
        */
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
    }


    if (SUCCEEDED(hr))
    {
        /*
        Direct3D 장치에 바인딩된 리소스를 만듭니다.
        Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
        리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
        */
        RECT rc;
        GetClientRect(g_hWnd, &rc);

        g_ScreenSize = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top);

        // Create a Direct2D render target.
        hr = g_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(g_hWnd, g_ScreenSize),
            &g_pRenderTarget);
    }

    if (SUCCEEDED(hr))
    {
        // Create WIC factory
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&g_pWICFactory)
        );
    }

	if (SUCCEEDED(hr))
	{
		hr = CreateD2DBitmapFromFile(L"../Resource/tree.jpg", &g_pD2DBitmap);
	}

    if (SUCCEEDED(hr))
    {
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(g_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&g_pDWriteFactory));
    }

	if (SUCCEEDED(hr))
	{
	    // DirectWrite 텍스트 형식 개체를 만듭니다.
	    hr = g_pDWriteFactory->CreateTextFormat(
		    L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		    NULL,
		    DWRITE_FONT_WEIGHT_NORMAL,
		    DWRITE_FONT_STYLE_NORMAL,
		    DWRITE_FONT_STRETCH_NORMAL,
		    15.0f,   // Font Size
		    L"", //locale
		    &g_pDWriteTextFormat
	    );
    }
    
  
    if (SUCCEEDED(hr))
    {
        hr = g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), &g_pBrush);
    }

    if (FAILED(hr))
    {
        _com_error err(hr);
        ::MessageBox(g_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
        return false;
    }


    return true;
}

void UninitDirect2D()
{
    if (g_pD2DBitmap)   g_pD2DBitmap->Release();
    if (g_pWICFactory) g_pWICFactory->Release();
    if (g_pRenderTarget) g_pRenderTarget->Release();
    if (g_pD2DFactory) g_pD2DFactory->Release();

    // COM 사용 끝
    CoUninitialize();
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_D2DCOORDINATESYSTEM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    InitDirect2D();


    MSG msg;
    // 기본 메시지 루프입니다:
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            //윈도우 메시지 처리 
            TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
            DispatchMessage(&msg);
        }
        else
        {
        
            // screen 좌표계에서 y축 반전 하므로  이전에 이미 반전하게한다.  매프레임계산 필요없음
            g_matRender = Matrix3x2F::Scale(1.0f, -1.0f); 

            // 왼쪽 하단이 원점이 되게하는 변환  매프레임계산 필요없음
			g_matScreen = Matrix3x2F::Scale(1.0f, -1.0f) * Matrix3x2F::Translation(0.0f, (float)g_ScreenSize.height); 

            // 카메라의 월드위치로 역행렬을 계산하여 카메라 좌표계로 변환하는 행렬
            g_matCamera = D2D1::Matrix3x2F::Translation(g_locCameraX,g_locCameraY);
            D2D1InvertMatrix(&g_matCamera);
          
            // 이미지의 위치는 월드좌표계로 값으로 설정
            g_matWorld = Matrix3x2F::Translation(0.0f, 768.0f); // 월드좌표 0,0은 스크린의 왼쪽 하단이 될수도 상단이 될수도 있다.

            D2D_MATRIX_3X2_F Transform = g_matRender * g_matWorld * g_matCamera * g_matScreen;

            g_pRenderTarget->BeginDraw();
            g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));            
            g_pRenderTarget->SetTransform(Transform);            
            g_pRenderTarget->DrawBitmap(g_pD2DBitmap);


            PrintMatrix(L"Transform", Transform, 0, 100);
            PrintMatrix(L"g_matRender", g_matRender, 200, 100);
            PrintMatrix(L"g_matWorld", g_matWorld, 300, 100);
            PrintMatrix(L"g_matCamera", g_matCamera, 400, 100);
            PrintMatrix(L"g_matScreen", g_matScreen, 500, 100);

            g_pRenderTarget->EndDraw();
        }
    }


    UninitDirect2D();

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D2DCOORDINATESYSTEM));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	// 원하는 크기가 조정되어 리턴
	RECT rcClient = { 0, 0, (LONG)1024, (LONG)768 };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	//생성
    g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		100, 100,	// 시작 위치
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
    {
        return FALSE;
    }

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    SetWindowText(g_hWnd,L"화살표 키로 카메라 이동합니다 ");

    return TRUE;
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::wstring str;
    switch (message)
    {
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
		    g_locCameraX -= 10;
		}
		else if (wParam == VK_RIGHT)
		{
            g_locCameraX += 10;
		}
		else if (wParam == VK_UP)
		{
		    g_locCameraY +=10;
		}
		else if (wParam == VK_DOWN)
		{
		    g_locCameraY -= 10;
		}	
             
     
        str = L"Camera X : " + to_wstring(g_locCameraX) + L" Camera Y : " + std::to_wstring(g_locCameraY);
        SetWindowText(hWnd, str.c_str());
		break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {

    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
