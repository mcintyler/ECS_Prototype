#pragma once
#include <vector>
#include "Components.h"
#include "Entity.h"

class ECS {
private:
	static ECS* m_instance;
	ECS();

	std::vector<Entity> m_entityPool;
	std::vector<int> m_deadEntityIDs;

public:
	~ECS();
	static ECS* GetInstance();

	void CreateEntity();
	void KillEntity(int id);
};