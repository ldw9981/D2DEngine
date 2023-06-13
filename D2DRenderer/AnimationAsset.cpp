#include "pch.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"

AnimationAsset::AnimationAsset()
	:m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
	// 참조카운터가 0이면 완전히 제거되기전에  Factory에 더 이상 공유하지않는다고 알린다 .
	D2DRenderer::m_Instance->ReleaseD2DBitmapFromFile(m_pBitmap);	
}

/*
	데이터를 가지고 새로운 데이터를 만들어내는것
*/
void AnimationAsset::Build()
{
	D2DRenderer::m_Instance->CreateD2DBitmapFromFile(m_BitmapFilePath, &m_pBitmap);
}

void AnimationAsset::SetBitmapFilePath(const WCHAR* szFilePath)
{
	m_BitmapFilePath = szFilePath;
}

