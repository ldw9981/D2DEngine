#include "TestFactory.h"
#include "GameObject.h"
#include "PlayerCharacter.h"

int TestFactory() 
{
	GameObject* pObject = GameObjectFactory::CreateGameObject("PlayerCharacter");

	return 0;
}

