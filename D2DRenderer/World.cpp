#include "pch.h"
#include "World.h"

World::World()
{
}

bool World::Initialize()
{
	return true;
}

void World::Update()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Update();
	}
}

void World::Render(ID2D1RenderTarget* pRernderTarget)
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Render(pRernderTarget);
	}
}
