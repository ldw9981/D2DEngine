#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional> // For std::function


class GameObject;

// CPP에서 사용합니다.
#define REGISTER_GAMEOBJECT(GameObjectType) \
    GameObject* CreateGameObject##GameObjectType() { return new GameObjectType(); } \
    bool Registered##GameObjectType = Factory::RegisterGameObject(#GameObjectType, CreateGameObject##GameObjectType);


class Factory
{
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


	static std::map<std::string, GameObjectCreator>& GetRegistry() {
		static std::map<std::string, GameObjectCreator> registry;
		return registry;
	}
};

