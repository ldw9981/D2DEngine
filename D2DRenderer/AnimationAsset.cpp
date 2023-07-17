#include "pch.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include <fstream>
#include "Helper.h"


using nlohmann::ordered_json;

AnimationAsset::AnimationAsset()
	:m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
	// 참조카운터가 0이면 완전히 제거되기전에  Factory에 더 이상 공유하지않는다고 알린다 .
	if(m_pBitmap)
		D2DRenderer::m_Instance->ReleaseSharedD2DBitmap(m_pBitmap);	
}


void AnimationAsset::SetD2DBitmap(const WCHAR* szFilePath)
{
	m_BitmapFilePath = szFilePath;
	bool result = D2DRenderer::m_Instance->CreateSharedD2DBitmapFromFile(m_BitmapFilePath, &m_pBitmap);
}

ANIMATION_INFO* AnimationAsset::GetAnimationInfo(const char* AnimationName)
{
	for (auto& iter : m_Animations)
	{
		if (iter.m_Name == std::string(AnimationName))
		{
			return &iter;
		}
	}
	return nullptr;
}

void AnimationAsset::Save(const WCHAR* szFilePath)
{
	ordered_json obj ;

	obj["m_BitmapFilePath"] = D2DHelper::WStringToString(m_BitmapFilePath);

	for (size_t ianimation=0; ianimation <  m_Animations.size(); ianimation++)
	{
		ANIMATION_INFO& animation = m_Animations[ianimation];
		ordered_json animationObj;
		animationObj["Name"] = animation.m_Name;
		

		for (size_t iframe=0 ; iframe < animation.m_Frames.size();iframe++)
		{
			FRAME_INFO& frame = animation.m_Frames[iframe];
			ordered_json frameObj;			
			frameObj["Source.left"] = frame.Source.left;
			frameObj["Source.top"] = frame.Source.top;
			frameObj["Source.right"] = frame.Source.right;
			frameObj["Source.bottom"] = frame.Source.bottom;
			frameObj["Center.x"] = frame.Center.x;
			frameObj["Center.y"] = frame.Center.y;
			frameObj["RenderTime"] = (frame.RenderTime);	
			animationObj["m_Frames"].push_back(frameObj);
		}
		obj["m_Animations"].push_back(animationObj);
	}

	std::ofstream ofs(szFilePath);
	ofs << obj.dump(2);
	ofs.close();
}

bool AnimationAsset::Load(const WCHAR* szFilePath)
{
	std::ifstream ifs(szFilePath,std::ios::in);
	if (!ifs.is_open()) 
	{
		LOG_ERROR(L"File not found %s",szFilePath);
		return false;
	}
	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	ordered_json obj = ordered_json::parse(str);

	m_BitmapFilePath = D2DHelper::StringToWString(obj["m_BitmapFilePath"].get<std::string>());

	bool result = D2DRenderer::m_Instance->CreateSharedD2DBitmapFromFile(m_BitmapFilePath, &m_pBitmap);

	for (auto& animationObj : obj["m_Animations"])
	{
		ANIMATION_INFO animation;
		animation.m_Name = animationObj["Name"].get<std::string>();
		for (auto& frameObj : animationObj["m_Frames"])
		{
			FRAME_INFO frame;
			frame.Source.left = frameObj["Source.left"].get<float>();
			frame.Source.top = frameObj["Source.top"].get<float>();
			frame.Source.right = frameObj["Source.right"].get<float>();
			frame.Source.bottom = frameObj["Source.bottom"].get<float>();
			frame.Center.x = frameObj["Center.x"].get<float>();
			frame.Center.y = frameObj["Center.y"].get<float>();
			frame.RenderTime = frameObj["RenderTime"].get<float>();
			animation.m_Frames.push_back(frame);
		}
		m_Animations.push_back(animation);
	}
	return true;
}

