#pragma once
#include "Components.h"
#include "Entity.h"
#include <vector>

class ECS {
private:
	static ECS* m_instance;
	ECS();

	std::vector<Entity> m_entityPool;
	std::vector<int> m_deadEntityIDs;

public:
	~ECS();
	static ECS* GetInstance();

	bool Init(int totalComponents, ...);
	void FreeComponentStore();

	Entity* CreateEntity();
	void KillEntity(int eID);
};

// TODO: Query, get, etc. -> https://www.youtube.com/watch?v=s6TMa33niJo