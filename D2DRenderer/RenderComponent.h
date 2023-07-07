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
	D2D1_MATRIX_3X2_F	m_RenderTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f , Matrix3x2F::Translation(m_DstRect.right,0.0f)�� �����Ѵ�.
public:
	void SetZOrder(int zOrder) {  m_iZOrder = zOrder; }
	int GetZOrder() const { return m_iZOrder; }
	void SetVisible(bool visible) { m_bVisible = visible; }
	virtual void Render(ID2D1RenderTarget* pRenderTarget) = 0;

	static bool CompareRenderOrder(RenderComponent* a, RenderComponent* b)
	{
		return a->m_iZOrder < b->m_iZOrder;
	}
};

