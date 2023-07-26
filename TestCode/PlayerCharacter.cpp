#include "PlayerCharacter.h"
#include "TestFactory.h"

REGISTER_GAMEOBJECT(PlayerCharacter)

void PlayerCharacter::Render()
{
	AnimationRender::Render();
	m_BoxRenderer.Render();
}

void PlayerCharacter::Update(float DeltaTime)
{
	Movement::Update(DeltaTime);
	AnimationRender::Update(DeltaTime);
	m_BoxRenderer.Update(DeltaTime);

}

