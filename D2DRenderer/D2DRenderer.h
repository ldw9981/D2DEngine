#pragma once

#include <map>
#include <string>
#include <list>
#include <queue>

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
	static Matrix3x2F m_CameraTransformInv;		// ī�޶��� ��ǥ��� ��ȯ�ϴ� ���
	
private:
	ID2D1Factory* m_pD2DFactory;		// D2D ��ü �������̽� ������ ����	
	IWICImagingFactory* m_pWICFactory;	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	ID2D1SolidColorBrush* m_pBrush;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����
	IDXGIFactory4* m_pDXGIFactory;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter;		// ����ī�� ������ ���� ������ �������̽�

	std::list<std::pair<std::wstring, ID2D1Bitmap*>> m_SharingBitmaps;
	std::list<std::pair<std::wstring, AnimationAsset*>> m_SharingAnimationAssets;

	
	std::priority_queue<RenderComponent*> m_RenderQueue;
	void SetCameraTransform(const Matrix3x2F& worldTrasnform);
public:
	HRESULT Initialize();

	void DrawRectangle(ID2D1RenderTarget* pRenderTarget,D2D1_RECT_F rect, D2D1_COLOR_F color);
	void DrawCrossLine(ID2D1RenderTarget* pRenderTarget,D2D1_VECTOR_2F point = {0.0f,0.0f}, D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::LightGreen));
	void DrawEllipse(ID2D1RenderTarget* pRenderTarget,D2D1_ELLIPSE ellipse, D2D1_COLOR_F color);
	void DrawText(ID2D1RenderTarget* pRenderTarget,const std::wstring& string,D2D1_RECT_F rect, D2D1_COLOR_F color);
	void EndDraw();


	// �����ϴ� ��Ʈ�� ����
	HRESULT CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	// �����̸����� �о�;������� �׳� ����ִ� �ν��Ͻ� �����Ѵ�.
	AnimationAsset* CreateAnimationAsset(std::wstring strFilePath);

	// ����� ��� ȣ���ϸ鼭 ī���Ͱ� 0�̵Ǹ� �������� ��Ͽ��� �����Ѵ�.
	void ReleaseD2DBitmapFromFile(ID2D1Bitmap* pBitmap);
	void ReleaseAnimationAsset(AnimationAsset* pAnimationAsset);
	ID2D1SolidColorBrush* GetBrush() const { return m_pBrush; }

	size_t GetUsedVRAM();
	void RenderQueue(ID2D1RenderTarget* pRenderTarget);
};

