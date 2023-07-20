#pragma once
#include "RenderComponent.h"
#include "D2DRenderer.h"
class BitmapComponent :
    public RenderComponent
{
public:
    BitmapComponent(GameObject* pOwner, const std::string& Name)
        :RenderComponent(pOwner, Name)
    {
        D2DRenderer::m_Instance->CreateSharedD2DBitmapFromFile(NOIMAGE,&m_pBitmap);
    }
    ~BitmapComponent()
    {
        if (m_pBitmap)
            D2DRenderer::m_Instance->ReleaseSharedD2DBitmap(m_pBitmap);
    }
protected:
    std::wstring m_FilePath;
    ID2D1Bitmap* m_pBitmap = nullptr;
public:
	std::wstring GetFilePath() const { return m_FilePath; }
	void SetBitmap(std::wstring val);

	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

    virtual void SerializeOut(nlohmann::ordered_json& object);
    virtual void SerializeIn(nlohmann::ordered_json& object);
};

