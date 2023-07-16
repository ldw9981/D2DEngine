#pragma once
#include "RenderComponent.h"
#include "D2DRenderer.h"
class BitmapComponent :
    public RenderComponent
{
public:
    BitmapComponent(GameObject* pOwner, const std::wstring& Name)
        :RenderComponent(pOwner, Name)
    {
        HRESULT  hr = D2DRenderer::m_Instance->CreateSharedD2DBitmapFromFile(Name,&m_pBitmap);
        if (FAILED(hr))
        {
            hr = D2DRenderer::m_Instance->CreateSharedD2DBitmapFromFile(NOIMAGE, &m_pBitmap);
        }
    }
    ~BitmapComponent()
    {
        D2DRenderer::m_Instance->ReleaseSharedD2DBitmap(m_pBitmap);
    }
protected:
    std::wstring m_FilePath;
    ID2D1Bitmap* m_pBitmap = nullptr;
public:
	std::wstring GetFilePath() const { return m_FilePath; }
	void SetFilePath(std::wstring val) { m_FilePath = val; }
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
};

