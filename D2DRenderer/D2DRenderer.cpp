// D2DRenderer.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "D2DRenderer.h"
#include "GameApp.h"

#pragma comment(lib,"d2d1.lib")

// TODO: 라이브러리 함수의 예제입니다.
void fnD2DRenderer()
{
}

ID2D1HwndRenderTarget* D2DRenderer::m_pRenderTarget= nullptr;

D2DRenderer::D2DRenderer()
    :m_pD2DFactory(nullptr),m_pWICFactory(nullptr)
{

}

D2DRenderer::~D2DRenderer()
{
}

HRESULT D2DRenderer::Initialize()
{
    HRESULT hr = S_OK;
    // COM 사용 시작
    hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        /*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
            이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
            DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
        */
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
    }
    if (SUCCEEDED(hr))
    {
        /*
        Direct3D 장치에 바인딩된 리소스를 만듭니다.
        Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
        리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
        */
      
        RECT rc;
        ::GetClientRect(GameApp::m_hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top);

        // Create a Direct2D render target.
        hr = m_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(GameApp::m_hWnd, size),
            &m_pRenderTarget);
    }

    if (SUCCEEDED(hr))
    {
        // Create WIC factory
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_pWICFactory)
        );
    }



    return hr;
}


void D2DRenderer::EndDraw()
{
	HRESULT hr = m_pRenderTarget->EndDraw();
	// 실패시 렌더타겟 재성성이지만 실패는 그래픽아답터 제거
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{
	HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = m_pWICFactory->CreateDecoderFromFilename(
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
		hr = m_pWICFactory->CreateFormatConverter(&pConverter);
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
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
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


void D2DRenderer::Finalize()
{
	if (m_pWICFactory) m_pWICFactory->Release();
	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pD2DFactory) m_pD2DFactory->Release();

	// COM 사용 끝
	CoUninitialize();
}
