#pragma once
#include "Object.h"
#include "GameObject.h"
#include "Helper.h"

/*
	월드는 GameObject를 생성하고 파괴하는 역할을 한다.
	또한 게임 오브젝트들의 Update, Render를 호출한다.
*/
class GameObject;
class RenderComponent;
class CameraComponent;
class World :
	public Object
{
public:
	World(std::string Name);
    virtual ~World()
	{
		Clear();
	}


	void OnBeginPlay();
	void OnEndPlay();

	virtual void Update(float DeltaTime);
	void Render(ID2D1RenderTarget* pRernderTarget);

	// 월드에서 컬링에서 필요한 카메라 컴포넌트를 설정한다 SceneComponent에 AABB가 들어있다.


	void SetCameraID(int id);
	bool UpdateReferenceCameraComponent(int id);
protected:
	std::vector<RenderComponent*> m_RenderQueue;		// 정렬을 위해 임의 접근이 빠르고 뒤쪽에만 추가하는 컨테이너는 무엇이 좋을까
    std::list<GameObject*> m_GameObjects;	// 생성된 게임 오브젝트들
	CameraComponent* m_pCamera;				// 컬링용도로 사용할 카메라
	int m_nCulledObjectCount;
	std::string m_Name;
	int m_CameraID;
	std::list<CameraComponent*> m_Cameras;	
	bool m_Playing;
public:
	void SetName(const std::string& Name) { m_Name = Name; }
	// 템플릿 함수로 GameObject를 생성한다.
    template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);

	virtual void Save(const wchar_t* FilePath);
	virtual bool Load(const wchar_t* FilePath);
	
	void AddCamera(CameraComponent* pCameraComponent);
	void DelCamera(CameraComponent* pCameraComponent);

	template<typename T>
	void GetGameObject(std::vector<GameObject*>& out)
	{
		for (auto& gameObject : m_GameObjects)
		{
			T Class;
			std::string a(gameObject->GetClassName());
			std::string b(Class.GetClassName());
			if (a != b)
				continue;

			out.push_back(gameObject);
		}
	}

	void Clear()
	{
		for (auto& gameObject : m_GameObjects)
		{
			delete gameObject;
		}
		m_GameObjects.clear();
		m_Cameras.clear();
	}
};

