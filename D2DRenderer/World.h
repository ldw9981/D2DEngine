#pragma once
#include "Object.h"
#include "GameObject.h"
/*
	����� GameObject�� �����ϰ� �ı��ϴ� ������ �Ѵ�.
	���� ���� ������Ʈ���� Update, Render�� ȣ���Ѵ�.
*/
class CameraComponent;
class World 
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

	virtual void Update();
	void Render(ID2D1RenderTarget* pRernderTarget);

	// ���忡�� �ø����� �ʿ��� ī�޶� ������Ʈ�� �����Ѵ� SceneComponent�� AABB�� ����ִ�.
	void SetCamera(CameraComponent* pCameraComponent) { m_pCamera = pCameraComponent; }

	// ī�޶� �������� �������� �ø��Ѵ�.
	void CullGameObject();
protected:
    std::list<GameObject*> m_GameObjects;	// ������ ���� ������Ʈ��
	CameraComponent* m_pCamera;				// �ø��뵵�� ����� ī�޶�
	int m_nCullCount = 0;					// �ø��� ������Ʈ�� ��
public:
	
	// ���ø� �Լ��� GameObject�� �����Ѵ�.
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

