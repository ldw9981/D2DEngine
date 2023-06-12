#include "pch.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"

AnimationAsset::AnimationAsset()
	:m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
	int a = m_pBitmap->Release();
}

/*
	�����͸� ������ ���ο� �����͸� �����°�
*/
void AnimationAsset::Build()
{
	D2DRenderer::m_Instance->CreateD2DBitmapFromFile(m_BitmapFilePath, &m_pBitmap);
}

void AnimationAsset::SetBitmapFilePath(const WCHAR* szFilePath)
{
	m_BitmapFilePath = szFilePath;
}