#pragma once

#define NOIMAGE L"../Resource/NoImage.png"
/*
	Direct2D�� �⺻ ����� ������ Ŭ����
	�⺻ ���� Ÿ���� �����Ѵ�.
	������ ���ҽ������� �μ� �����ϴ� ��Ʈ�ʰ� 
	�����ϴ� �ִϸ��̼� ����� �����ϴ� ����� �����Ѵ�.
*/
class AnimationAsset;
class RenderComponent;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
	static D2DRenderer* m_Instance;
	static D2D1_MATRIX_3X2_F m_CameraTransform;		// ī�޶��� ��ǥ��� ��ȯ�ϴ� ���
	static D2D1_MATRIX_3X2_F m_ScreenTransform;		// ���� �ϴ��� 0,0�� ȭ���� ��ǥ��� ��ȯ�ϴ� ���   
private:
	ID2D1Factory* m_pD2DFactory;		// D2D ��ü �������̽� ������ ����	
	IWICImagingFactory* m_pWICFactory;	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	ID2D1SolidColorBrush* m_pBrush;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����
	IDXGIFactory4* m_pDXGIFactory;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter;		// ����ī�� ������ ���� ������ �������̽�
	HWND m_hWnd;

	std::list<std::pair<std::wstring, ID2D1Bitmap*>> m_SharingBitmaps;
	std::list<std::pair<std::wstring, AnimationAsset*>> m_SharingAnimationAssets;	
public:
	HRESULT Initialize(HWND hWnd);

	void DrawRectangle(ID2D1RenderTarget* pRenderTarget,D2D1_RECT_F rect, D2D1_COLOR_F color);
	void DrawCrossLine(ID2D1RenderTarget* pRenderTarget,D2D1_VECTOR_2F point = {0.0f,0.0f}, D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::LightGreen));
	void DrawEllipse(ID2D1RenderTarget* pRenderTarget,D2D1_ELLIPSE ellipse, D2D1_COLOR_F color);
	void DrawText(ID2D1RenderTarget* pRenderTarget,const std::wstring& string,D2D1_RECT_F rect, D2D1_COLOR_F color);



	// ī�޶��� ���� ��ȯ�� �־� ������� ����Ͽ� �����Ѵ�.
	void SetCameraTransform(const D2D1_MATRIX_3X2_F& worldTrasnform);
	// �����ϴ� ��Ʈ�� ����
	bool CreateSharedD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	// �����̸����� �о�;������� �׳� ����ִ� �ν��Ͻ� �����Ѵ�.
	AnimationAsset* CreateSharedAnimationAsset(std::wstring strFilePath);

	// ����� ��� ȣ���ϸ鼭 ī���Ͱ� 0�̵Ǹ� �������� ��Ͽ��� �����Ѵ�.
	void ReleaseSharedD2DBitmap(ID2D1Bitmap* pBitmap);
	void ReleaseSharedAnimationAsset(AnimationAsset* pAnimationAsset);
	ID2D1SolidColorBrush* GetBrush() const { return m_pBrush; }

	size_t GetUsedVRAM();
	D2D_SIZE_U GetClientSize();

	static void UpdateScreenTransform(D2D_SIZE_U ScreenSize);
};

