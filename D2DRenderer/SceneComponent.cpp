#include "pch.h"
#include "SceneComponent.h"
#include "Helper.h"
#include "GameObject.h"
#include "D2DRenderer.h"

SceneComponent::SceneComponent(GameObject* pOwner, std::string Name)
	:Component(pOwner, Name),
	m_RelativeScale({ 1.0f,1.0f }),
	m_RelativeRotation(0.0f), 
	m_RelativeLocation({ 0.0f,0.0f }), 
	m_RelativeTransform(D2D1::Matrix3x2F::Identity()), 
	m_pParentScene(nullptr),
	m_WorldTransform(D2D1::Matrix3x2F::Identity())
{
	m_Velocity = { 0.0f,0.0f };
}


bool SceneComponent::Initialize()
{
	return true;
}

void SceneComponent::Update(float DeltaTime)
{
	UpdateTrasnform();	
	UpdateVelocity();
}

void SceneComponent::UpdateTrasnform()
{
	m_RelativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	if (m_pParentScene != nullptr)
	{	
		// 자식변환을 먼저 적용한다.
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	}
	else
	{
		m_WorldTransform = m_RelativeTransform;
	}
	
	m_BoundingBox.m_Center = GetWorldLocation();
}

void SceneComponent::UpdateVelocity()
{
	if (m_pParentScene != nullptr)
	{
		m_Velocity = m_pParentScene->GetVelocity();
	}	
}

void SceneComponent::SetRelativeScale(float x, float y)
{
	m_RelativeScale = { x,y };
}

void SceneComponent::AddRelativeScale(float x, float y)
{
	m_RelativeScale = { m_RelativeScale.x + x,m_RelativeScale.y + y };
}

void SceneComponent::SetRelativeRotation(float Rotation)
{
	m_RelativeRotation = Rotation;
}

void SceneComponent::AddRelativeRotation(float Rotation)
{
	m_RelativeRotation += Rotation;
	m_RelativeRotation = fmodf(m_RelativeRotation, 360.0f);
}

void SceneComponent::SetRelativeLocation(const mathHelper::Vector2F& Location)
{
	m_RelativeLocation = Location;
}

void SceneComponent::AddRelativeLocation(float x, float y)
{
	m_RelativeLocation = { m_RelativeLocation.x + x,m_RelativeLocation.y + y };
}

void SceneComponent::AttachToComponent(SceneComponent* pParent)
{
	m_pParentScene = pParent;
	pParent->m_Children.push_back(this);
}

// WorldTransform 디버깅용
void SceneComponent::DrawDebugWorldTransform(ID2D1RenderTarget* pRenderTarget)
{
	D2D1_MATRIX_3X2_F Transform = m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	pRenderTarget->SetTransform(Transform);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

void SceneComponent::SerializeOut(nlohmann::ordered_json& object)
{
	__super::SerializeOut(object);
	
	object["m_RelativeLocation"] = { m_RelativeLocation.x,m_RelativeLocation.y };	
}

void SceneComponent::SerializeIn(nlohmann::ordered_json& object)
{
	__super::SerializeIn(object);
	

	if (object.find("m_RelativeScale") != object.end())
	{
		m_RelativeScale.x = object["m_RelativeScale"][0];
		m_RelativeScale.y = object["m_RelativeScale"][1];	
	}
	if (object.find("m_RelativeRotation") != object.end())
	{
		m_RelativeRotation = object["m_RelativeRotation"];
	}

	if (object.find("m_RelativeLocation") != object.end())
	{
		m_RelativeLocation.x = object["m_RelativeLocation"][0];
		m_RelativeLocation.y = object["m_RelativeLocation"][1];
	}
	if (object.find("m_BoundingBox.m_Extend") != object.end())
	{
		m_BoundingBox.m_Extend.x = object["m_BoundingBox.m_Extend"][0];
		m_BoundingBox.m_Extend.y = object["m_BoundingBox.m_Extend"][1];
	}
}

void SceneComponent::OnBeginPlay()
{

}

void SceneComponent::OnEndPlay()
{

}
