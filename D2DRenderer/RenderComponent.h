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
	RenderComponent(GameObject* pOwner,const std::string&  Name);
	virtual ~RenderComponent();

protected:
	int m_ZOrder;		// �׸��� ����
	bool m_Visible;	// �׸�������
	D2D1_MATRIX_3X2_F	m_RenderTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 
public:
	void SetZOrder(int zOrder) {  m_ZOrder = zOrder; }
	int GetZOrder() const { return m_ZOrder; }
	void SetVisible(bool visible) { m_Visible = visible; }
	virtual void Render(ID2D1RenderTarget* pRenderTarget) = 0;

	static bool CompareRenderOrder(RenderComponent* a, RenderComponent* b)
	{
		return a->m_ZOrder < b->m_ZOrder;
	}

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
};

