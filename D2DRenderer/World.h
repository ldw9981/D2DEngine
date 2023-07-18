#pragma once
#include "Object.h"
#include "GameObject.h"
/*
	월드는 GameObject를 생성하고 파괴하는 역할을 한다.
	또한 게임 오브젝트들의 Update, Render를 호출한다.
*/
class RenderComponent;
class CameraComponent;
class World :
	public Object
{
public:
	World(std::string Name)
	:m_Name(Name)
	{

	}
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

	// 월드에서 컬링에서 필요한 카메라 컴포넌트를 설정한다 SceneComponent에 AABB가 들어있다.
	void SetCamera(CameraComponent* pCameraComponent) { m_pCamera = pCameraComponent; }


protected:
	std::vector<RenderComponent*> m_RenderQueue;		// 정렬을 위해 임의 접근이 빠르고 뒤쪽에만 추가하는 컨테이너는 무엇이 좋을까
    std::list<GameObject*> m_GameObjects;	// 생성된 게임 오브젝트들
	CameraComponent* m_pCamera;				// 컬링용도로 사용할 카메라
	int m_nCulledObjectCount;
	std::string m_Name;
public:
	
	// 템플릿 함수로 GameObject를 생성한다.
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

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object) { };

	virtual void Save(const wchar_t* FilePath);
};

