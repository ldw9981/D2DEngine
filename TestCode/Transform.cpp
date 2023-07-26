#include "Transform.h"
#include <iostream>

void Transform::Update(float DeltaTime)
{
	std::cout << L"Transform Update" << std::endl ;
	m_RelativeTransform = m_RelativePositionX;

	if(m_pParent)
	{ 
		m_WorldTransform = m_RelativeTransform + m_pParent->m_WorldTransform;
	}
	else
	{
		m_WorldTransform = m_RelativeTransform;
	}
}
