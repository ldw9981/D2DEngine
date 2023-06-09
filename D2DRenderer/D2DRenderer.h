#pragma once


class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
public:
	//  D2D ��ü �������̽� ������ ����
	ID2D1Factory* m_pD2DFactory = nullptr;
	// D2D1��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IWICImagingFactory* m_pWICFactory = nullptr;
public:
	HRESULT Initialize();

	void EndDraw();

	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	void Finalize();
};

