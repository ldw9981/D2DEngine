// D2DRenderer.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "D2DRenderer.h"
#include "GameApp.h"
#include "AnimationAsset.h"
#include "AnimationInstance.h"

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")


ID2D1HwndRenderTarget* D2DRenderer::m_pRenderTarget= nullptr;
D2DRenderer* D2DRenderer::m_Instance = nullptr;

D2DRenderer::D2DRenderer()
    :m_pD2DFactory(nullptr),m_pWICFactory(nullptr),m_pDWriteFactory(nullptr), m_pDWriteTextFormat(nullptr)
{
	OutputDebugString(L"D2DRenderer::D2DRenderer()\n");
	m_Instance = this;
}

D2DRenderer::~D2DRenderer()
{
	OutputDebugString(L"D2DRenderer::~D2DRenderer()\n");
	if (m_pWICFactory) m_pWICFactory->Release();
	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pD2DFactory) m_pD2DFactory->Release();

	// COM 사용 끝
	CoUninitialize();
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

	if (SUCCEEDED(hr))
	{
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite 텍스트 형식 개체를 만듭니다.
		hr = m_pDWriteFactory->CreateTextFormat(
			L"Cooper", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20.0f,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}	

	if (SUCCEEDED(hr))
	{
		// 텍스트를 수평 및 수직으로 중앙에 맞춥니다.
		//m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		//m_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
    return hr;
}


void D2DRenderer::EndDraw()
{
	HRESULT hr = m_pRenderTarget->EndDraw();
	// 실패시 렌더타겟 재성성이지만 실패는 그래픽아답터 제거
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{	
	// 문자열과 포인터 쌍에서 문자열만 같으면 해당 원소를 찾는다.
	auto it = std::find_if(m_SharingBitmaps.begin(), m_SharingBitmaps.end(), 
		[strFilePath](std::pair<std::wstring, ID2D1Bitmap*> ContainerData)
		{
			return ( ContainerData.first == strFilePath);
		}
	);

	// 컨테이너에 이미 같은 경로가 있으면 다시 만들지 않는다. 
	// 즉 기존 비트맵의 레퍼런스 증가시키고 포인터 변수에 값을 넣는다.
	HRESULT hr;
	if (it != m_SharingBitmaps.end())
	{
		ID2D1Bitmap* pBitmap = (*it).second;
		*ppID2D1Bitmap = pBitmap;
		pBitmap->AddRef();
		hr=S_OK;
		return hr;
	}

	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = m_pWICFactory->CreateDecoderFromFilename(
		strFilePath.c_str(),                      // Image to be decoded
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


	m_SharingBitmaps.push_back(std::pair<std::wstring, ID2D1Bitmap*>(strFilePath,*ppID2D1Bitmap));
	return hr;
}


AnimationAsset* D2DRenderer::CreateAnimationAsset(std::wstring key)
{
	// 문자열과 포인터 쌍에서 문자열만 같으면 해당 원소를 찾는다.
	auto it = std::find_if(m_SharingAnimationAssets.begin(), m_SharingAnimationAssets.end(),
		[key](std::pair<std::wstring, AnimationAsset*> ContainerData)
		{
			return (ContainerData.first == key);
		}
	);
	// 컨테이너에 이미 같은 경로가 있으면 다시 만들지 않는다. 
	// 즉 기존 비트맵의 레퍼런스 증가시키고 포인터 변수에 값을 넣는다.
	AnimationAsset* pAnimationAsset=nullptr;
	if (it != m_SharingAnimationAssets.end())
	{
		pAnimationAsset = (*it).second;
		pAnimationAsset->AddRef();
		return pAnimationAsset;
	}
	pAnimationAsset = new AnimationAsset;
	pAnimationAsset->SetKey(key);

	m_SharingAnimationAssets.push_back(std::pair<std::wstring, AnimationAsset*>(key, pAnimationAsset));

	pAnimationAsset->AddRef();
	return pAnimationAsset;
}

void D2DRenderer::ReleaseD2DBitmapFromFile(ID2D1Bitmap* pBitmap)
{
	int cnt = pBitmap->Release();

	if (cnt > 0)
		return;

	// 문자열과 포인터 쌍에서 포인터만 같으면 원소를 찾아서 지운다.
	auto it = std::find_if(m_SharingBitmaps.begin(), m_SharingBitmaps.end(),
		[pBitmap](std::pair<std::wstring, ID2D1Bitmap*> ContainerData)
		{
			return (ContainerData.second == pBitmap);
		}
	);
	if (it != m_SharingBitmaps.end())
	{
		m_SharingBitmaps.erase(it);		
	}
}

void D2DRenderer::ReleaseAnimationAsset(AnimationAsset* pAnimationAsset)
{
	int cnt = pAnimationAsset->Release();
	if (cnt > 0)
		return;

	// 문자열과 포인터 쌍에서 포인터만 같으면 원소를 찾아서 지운다.
	auto it = std::find_if(m_SharingAnimationAssets.begin(), m_SharingAnimationAssets.end(),
		[pAnimationAsset](std::pair<std::wstring, AnimationAsset*> ContainerData)
		{
			return (ContainerData.second == pAnimationAsset);
		}
	);
	if (it != m_SharingAnimationAssets.end())
	{
		m_SharingAnimationAssets.erase(it);
	}
}

