#pragma once
#include "../DEFINITIONS.h"
#include "Components.h"
#include "ComponentStore.h"
#include <vector>
#include <bitset>

enum EntityFlags {
	IS_ALIVE
};

class Entity {
private:
	ComponentStore m_componentStore;
	std::bitset<MaxComponents> m_componentMask;
	int m_eID = -1;

public:
	std::bitset<1> m_flags;

	Entity(int eID);
	~Entity();

	void AddComponent(ComponentID cID, void* data);
	void RemoveComponent(ComponentID cID);
	void ClearComponents();
	void* GetComponent(ComponentID cID);
};