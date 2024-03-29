#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional> // For std::function


int TestFactory();

// Registration macros to simplify registration of concrete products
#define REGISTER_GAMEOBJECT(GameObjectType) \
    GameObject* Create##GameObjectType() { return new GameObjectType(); } \
    bool Registered##GameObjectType = GameObjectFactory::RegisterGameObject(#GameObjectType, Create##GameObjectType);

class GameObject;
// Factory class using registration mechanism
class GameObjectFactory {
public:
	using GameObjectCreator = std::function<GameObject* ()>;

	static GameObject* CreateGameObject(const std::string& GameObjectType) {
		auto it = GetRegistry().find(GameObjectType);
		if (it != GetRegistry().end()) {
			return it->second();
		}
		return nullptr;
	}

	static bool RegisterGameObject(const std::string& GameObjectType, GameObjectCreator creator) {
		GetRegistry()[GameObjectType] = creator;
		return true;
	}

private:
	static std::map<std::string, GameObjectCreator>& GetRegistry() {
		static std::map<std::string, GameObjectCreator> registry;
		return registry;
	}
};

