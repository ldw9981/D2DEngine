#pragma once
#include "Object.h"
#include <list>
#include "GameObject.h"
/*
	����� GameObject�� �����ϰ� �ı��ϴ� ������ �Ѵ�.
	���� ���� ������Ʈ���� Update, Render�� ȣ���Ѵ�.
*/
class CameraComponent;
class World :
    public Object
{
public:
    World();
    virtual ~World()
	{
		for (auto& gameObject : m_GameObjects)
		{
			delete gameObject;
		}
		m_GameObjects.clear();
	}

	virtual bool Initialize() override;
	virtual void Update() override;
	void Render(ID2D1RenderTarget* pRernderTarget);
	void SetCamera(CameraComponent* pCameraComponent) { m_pCamera = pCameraComponent; }

	void CullGameObject();
protected:
    std::list<GameObject*> m_GameObjects;
	CameraComponent* m_pCamera;				// �ø��뵵�� ����� ī�޶�
public:
    template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		newObject->SetOwnerWorld(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}
};

