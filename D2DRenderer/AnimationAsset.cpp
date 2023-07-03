#include "pch.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"

AnimationAsset::AnimationAsset()
	:m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
	// ����ī���Ͱ� 0�̸� ������ ���ŵǱ�����  Factory�� �� �̻� ���������ʴ´ٰ� �˸��� .
	if(m_pBitmap)
		D2DRenderer::m_Instance->ReleaseSharedD2DBitmap(m_pBitmap);	
}


void AnimationAsset::SetD2DBitmap(const WCHAR* szFilePath)
{
	m_BitmapFilePath = szFilePath;
	HRESULT hr = D2DRenderer::m_Instance->CreateSharedD2DBitmapFromFile(m_BitmapFilePath, &m_pBitmap);
}

ANIMATION_INFO* AnimationAsset::GetAnimationInfo(const WCHAR* AnimationName)
{
	for (auto& iter : m_Animations)
	{
		if (iter.m_Name == wstring(AnimationName))
		{
			return &iter;
		}
	}
	return nullptr;
}

