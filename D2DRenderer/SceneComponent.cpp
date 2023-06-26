#include "pch.h"
#include "SceneComponent.h"
#include "RendererHelper.h"
SceneComponent::SceneComponent()
	:m_RelativeScale({ 1.0f,1.0f }),
	m_RelativeRotation(0.0f), 
	m_RelativeLocation({ 0.0f,0.0f }), 
	m_RelativeTransform(Matrix3x2F::Identity()), 
	m_pParentScene(nullptr),
	m_WorldTransform(Matrix3x2F::Identity())
{

}


bool SceneComponent::Initialize()
{
	return true;
}

void SceneComponent::Update()
{
	UpdateTrasnform();	
}

void SceneComponent::UpdateTrasnform()
{
	m_RelativeTransform = Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		Matrix3x2F::Rotation(m_RelativeRotation) *
		Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	if (m_pParentScene != nullptr)
	{	
		// 자식변환을 먼저 적용한다.
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	}
	else
	{
		m_WorldTransform = m_RelativeTransform;
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

void SceneComponent::SetRelativeLocation(float x, float y)
{
	m_RelativeLocation = { x,y };
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
