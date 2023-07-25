#include "PlayerCharacter.h"
#include "TestFactory.h"

REGISTER_GAMEOBJECT(PlayerCharacter)

void PlayerCharacter::Render()
{
	AnimationRender::Render();
	m_BoxRenderer.Render();
}

void PlayerCharacter::Update()
{
	Movement::Update();
	AnimationRender::Update();
	m_BoxRenderer.Update();

}

