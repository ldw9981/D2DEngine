#include "pch.h"
#include "World.h"

World::World()
{
}

World::~World()
{
	for (auto& gameObject : m_GameObjectContainer)
	{
		delete gameObject;
	}	
	m_GameObjectContainer.clear();
}

bool World::Init()
{
	return true;
}

void World::Update()
{
	for (auto& gameObject : m_GameObjectContainer)
	{
		gameObject->Update();
	}
}

void World::Render(ID2D1RenderTarget* pRernderTarget)
{
	for (auto& gameObject : m_GameObjectContainer)
	{
		gameObject->Render(pRernderTarget);
	}
}
