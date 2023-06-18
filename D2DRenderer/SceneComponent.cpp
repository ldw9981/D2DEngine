#include "pch.h"
#include "SceneComponent.h"

SceneComponent::SceneComponent()
	:m_RelativeScale({ 1.0f,1.0f }), m_RelativeRotation(0.0f), m_RelativeLocation({ 0.0f,0.0f }), m_RelativeTransform(Matrix3x2F::Identity()), m_pParent(nullptr),m_WorldTransform(Matrix3x2F::Identity())
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
	m_RelativeTransform = Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		Matrix3x2F::Rotation(m_RelativeRotation) *
		Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);
	if (m_pParent!=nullptr)
	{
		m_WorldTransform = m_RelativeTransform * m_pParent->m_WorldTransform;
	}
	else
	{
		m_WorldTransform = m_RelativeTransform;
	}

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

void SceneComponent::AddChild(SceneComponent* pChild)
{
	m_Children.push_back(pChild);
	pChild->m_pParent = this;
}



D2D1_VECTOR_2F SceneComponent::ExtractScaleFromTransform(const D2D1_MATRIX_3X2_F& Transform)
{
	D2D1_VECTOR_2F Scale;
	Scale.x = sqrtf(Transform._11 * Transform._11 + Transform._12 * Transform._12);
	Scale.y = sqrtf(Transform._21 * Transform._21 + Transform._22 * Transform._22);
	return Scale;
}
