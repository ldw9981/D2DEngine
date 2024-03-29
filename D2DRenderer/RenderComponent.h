#pragma once
#include "SceneComponent.h"
/*
	Render를 사용하는 컴포넌트를 위한 추상 클래스
	게임 오브젝트에서  RenderComponent로 dynamic_cast를 하여 Render를 호출한다.

	그리는 순서와, 그리는지 여부를 가진다.
	지금은 우선순위 없이 Render를 호출해주고 있지만 
	카메라 컬링후에 실제 그리려는 자식클래스 인스턴스만 
	자식클래스의 포인터 주소를 ZOrder로 정렬하여 그리도록 한다.	
*/
class GameObject;
class RenderComponent: public SceneComponent
{
public:
	RenderComponent(GameObject* pOwner,const std::string&  Name);
	virtual ~RenderComponent();

protected:
	int m_ZOrder;		// 그리는 순서
	bool m_Visible;	// 그리려는지
	D2D1_MATRIX_3X2_F	m_RenderTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f 
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

