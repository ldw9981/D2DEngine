#include "TestFactory.h"
#include "GameObject.h"
#include "PlayerCharacter.h"

int TestFactory() 
{
	GameObject* pObject = ProductFactory::createProduct("PlayerCharacter");

	return 0;
}

