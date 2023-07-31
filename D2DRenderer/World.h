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
		Clear();
	}


	void OnBeginPlay();
	void OnEndPlay();

	virtual void Update(float DeltaTime);
	void Render(ID2D1RenderTarget* pRernderTarget);

	// ���忡�� �ø����� �ʿ��� ī�޶� ������Ʈ�� �����Ѵ� SceneComponent�� AABB�� ����ִ�.


	void SetCameraID(int id);
	bool UpdateReferenceCameraComponent(int id);
protected:
	std::vector<RenderComponent*> m_RenderQueue;		// ������ ���� ���� ������ ������ ���ʿ��� �߰��ϴ� �����̳ʴ� ������ ������
    std::list<GameObject*> m_GameObjects;	// ������ ���� ������Ʈ��
	CameraComponent* m_pCamera;				// �ø��뵵�� ����� ī�޶�
	int m_nCulledObjectCount;
	std::string m_Name;
	int m_CameraID;
	std::list<CameraComponent*> m_Cameras;	
	bool m_Playing;
public:
	void SetName(const std::string& Name) { m_Name = Name; }
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

