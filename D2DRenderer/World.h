#pragma once
#include "Object.h"
#include <list>
#include "GameObject.h"
/*
	월드는 GameObject를 생성하고 파괴하는 역할을 한다.
	또한 게임 오브젝트들의 Update, Render를 호출한다.
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
	CameraComponent* m_pCamera;				// 컬링용도로 사용할 카메라
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

