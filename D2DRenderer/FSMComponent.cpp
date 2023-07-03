#include "pch.h"
#include "FSMComponent.h"
#include "FSMInstance.h"

FSMComponent::~FSMComponent()
{
	if (m_pFSMInstance != nullptr)
		delete m_pFSMInstance;

}


void FSMComponent::Update()
{
	if (m_pFSMInstance != nullptr)
		m_pFSMInstance->Update();
}
