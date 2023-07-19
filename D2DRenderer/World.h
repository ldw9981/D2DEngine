#pragma once
#include "Object.h"
#include "GameObject.h"
/*
	����� GameObject�� �����ϰ� �ı��ϴ� ������ �Ѵ�.
	���� ���� ������Ʈ���� Update, Render�� ȣ���Ѵ�.
*/

class GameObject;
using ClassCreator = GameObject* (*)();

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
	void SetCamera(CameraComponent* pCameraComponent) { m_pCamera = pCameraComponent; }


protected:
	std::vector<RenderComponent*> m_RenderQueue;		// ������ ���� ���� ������ ������ ���ʿ��� �߰��ϴ� �����̳ʴ� ������ ������
    std::list<GameObject*> m_GameObjects;	// ������ ���� ������Ʈ��
	CameraComponent* m_pCamera;				// �ø��뵵�� ����� ī�޶�
	int m_nCulledObjectCount;
	std::string m_Name;
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

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);

	virtual void Save(const wchar_t* FilePath);
	virtual bool Load(const wchar_t* FilePath);

	static std::map<std::string, ClassCreator> m_ClassCreator;
	static void RegisterCreator(const std::string& ClassName,ClassCreator func)
	{
		m_ClassCreator[ClassName] = func;
	}
};

