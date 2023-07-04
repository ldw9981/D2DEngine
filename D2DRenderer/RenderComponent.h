#pragma once
#include "SceneComponent.h"
/*
	Render�� ����ϴ� ������Ʈ�� ���� �߻� Ŭ����
	���� ������Ʈ����  RenderComponent�� dynamic_cast�� �Ͽ� Render�� ȣ���Ѵ�.

	�׸��� ������, �׸����� ���θ� ������.
	������ �켱���� ���� Render�� ȣ�����ְ� ������ 
	ī�޶� �ø��Ŀ� ���� �׸����� �ڽ�Ŭ���� �ν��Ͻ��� 
	�ڽ�Ŭ������ ������ �ּҸ� ZOrder�� �����Ͽ� �׸����� �Ѵ�.	
*/
class GameObject;
class RenderComponent: public SceneComponent
{
public:
	RenderComponent(GameObject* pOwner,const std::wstring&  Name);
	virtual ~RenderComponent();

protected:
	int m_iZOrder;		// �׸��� ����
	bool m_bVisible;	// �׸�������
	
public:
	void SetZOrder(int zOrder) {  m_iZOrder = zOrder; }
	void SetVisible(bool visible) { m_bVisible = visible; }
	virtual void Render(ID2D1RenderTarget* pRenderTarget) = 0;
	
	bool operator<(const RenderComponent& rhs)
	{
		return m_iZOrder < rhs.m_iZOrder;
	}

};

