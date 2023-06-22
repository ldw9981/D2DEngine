#pragma once
#include "SceneComponent.h"
/*
	Render�� ����ϴ� ������Ʈ�� ���� �߻� Ŭ����
	�׸��� ������, �׸����� ���θ� ������.
	������ �켱���� ���� Render�� ȣ�����ְ� ������ 
	ī�޶� �ø��Ŀ� ���� �׸����� �ڽ�Ŭ���� �ν��Ͻ��� 
	�ڽ�Ŭ������ ������ �ּҸ� ZOrder�� �����Ͽ� �׸����� �Ѵ�.
*/
class RenderComponent: public SceneComponent
{
public:
	RenderComponent();
	virtual ~RenderComponent();
protected:
	int m_iZOrder;		// �׸��� ����
	bool m_bVisible;	// �׸�������
public:
	void SetZOrder(int zOrder) {  m_iZOrder = zOrder; }
	void SetVisible(bool visible) { m_bVisible = visible; }
	virtual void Render(ID2D1RenderTarget* pRenderTarget) = 0;
};

