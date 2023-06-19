#include "pch.h"
#include "SceneComponent.h"

SceneComponent::SceneComponent()
	:m_RelativeScale({ 1.0f,1.0f }),m_RelativeRotation(0.0f), m_RelativeLocation({ 0.0f,0.0f }), m_RelativeTransform(Matrix3x2F::Identity()), m_pParent(nullptr),m_WorldTransform(Matrix3x2F::Identity())
{

}

SceneComponent::~SceneComponent()
{
	for (auto& pChild : m_Children)
	{
		delete pChild;
	}
	m_Children.clear();
}

bool SceneComponent::Init()
{
	return true;
}

void SceneComponent::Update()
{
	UpdateTrasnform();

	for (auto& pChild : m_Children)
	{
		pChild->Update();
	}
}

void SceneComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pChild : m_Children)
	{
		pChild->Render(pRenderTarget);
	}
	
}

void SceneComponent::UpdateTrasnform()
{
	m_RelativeTransform = Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		Matrix3x2F::Rotation(m_RelativeRotation) *
		Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	if (m_pParent != nullptr)
	{	
		// 자식변환을 먼저 적용한다.
		m_WorldTransform = m_RelativeTransform * m_pParent->m_WorldTransform;
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

void SceneComponent::SetRelativePosition(float x, float y)
{
	m_RelativeLocation = { x,y };
}

void SceneComponent::AddRelativePosition(float x, float y)
{
	m_RelativeLocation = { m_RelativeLocation.x + x,m_RelativeLocation.y + y };
}

D2D_VECTOR_2F SceneComponent::ExtractScaleFromTransform(const D2D1_MATRIX_3X2_F& Transform)
{
	D2D_VECTOR_2F Scale;
	Scale.x = sqrtf(Transform._11 * Transform._11 + Transform._12 * Transform._12);
	Scale.y = sqrtf(Transform._21 * Transform._21 + Transform._22 * Transform._22);
	return Scale;
}
