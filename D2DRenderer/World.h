#pragma once
#include "Object.h"
#include "GameObject.h"
#include "Helper.h"

/*
	����� GameObject�� �����ϰ� �ı��ϴ� ������ �Ѵ�.
	���� ���� ������Ʈ���� Update, Render�� ȣ���Ѵ�.
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
		for (auto& gameObject : m_GameObjects)
		{
			delete gameObject;
		}
		m_GameObjects.clear();
	}

	virtual void Update();
	void Render(ID2D1RenderTarget* pRernderTarget);

	// ���忡�� �ø����� �ʿ��� ī�޶� ������Ʈ�� �����Ѵ� SceneComponent�� AABB�� ����ִ�.


	void SetCamera(int id) 
	{ 
		auto it = m_Cameras.find(id);
		if (it == m_Cameras.end())
		{			
			m_pCamera = nullptr;
			LOG_ERROR(L"Camera ID  %d is not exist",id);
			// ã�� ī�޶� ������ ��� ó���ؾ��ұ�.
			return;
		}	
		m_CameraID = id; 
		m_pCamera = it->second;
	}

protected:
	std::vector<RenderComponent*> m_RenderQueue;		// ������ ���� ���� ������ ������ ���ʿ��� �߰��ϴ� �����̳ʴ� ������ ������
    std::list<GameObject*> m_GameObjects;	// ������ ���� ������Ʈ��
	CameraComponent* m_pCamera;				// �ø��뵵�� ����� ī�޶�
	int m_nCulledObjectCount;
	std::string m_Name;
	int m_CameraID;
	std::map<int, CameraComponent*> m_Cameras;	
public:
	
	// ���ø� �Լ��� GameObject�� �����Ѵ�.
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
	void GetGameObject(std::list<GameObject>& out)
	{
		for (auto& gameObject : m_GameObjects)
		{
			std::string a(typeid(*gameObject).name);
			std::string b(typeid(T).name);
			if (a != b)
				continue;

			out.push_back(gameObject);
		}
	}
};

