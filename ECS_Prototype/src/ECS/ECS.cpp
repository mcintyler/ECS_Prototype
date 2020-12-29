#include "../DEFINITIONS.h"
#include "ECS.h"
#include <stdio.h>

ECS* ECS::m_instance = nullptr;

ECS::ECS() {
	// Set minimum initial allocation size of entityPool
	m_entityPool.reserve(EntityPoolCapacity);
	printf("[ECS] EntityPoolCapacity = %d\n", EntityPoolCapacity);
}

ECS::~ECS() {

}

ECS* ECS::GetInstance() {
	if(m_instance == nullptr) {
		m_instance = new ECS();
	}
	return m_instance;
}

void ECS::CreateEntity() {
	int id = -1;

	if(m_deadEntityIDs.size() > 0) {
		// If available, use a dead entity's ID...
		id = m_deadEntityIDs.back();
		m_deadEntityIDs.pop_back();

		// Replace dead entity data
		m_entityPool.at(id) = Entity();
	} else {
		// ...else use next unallocated entity ID
		id = (int)m_entityPool.size();

		// Add new entity to the pool
		m_entityPool.push_back(Entity());
	}

	printf("[ECS] Created new Entity with id %d\n", id);
}

void ECS::KillEntity(int id) {
	// Clear all flags (including the isAlive flag to free this entity for future use)
	m_entityPool.at(id).m_flagMask = 0;

	// Add id to list of dead IDs
	m_deadEntityIDs.push_back(id);

	printf("[ECS] Killed Entity with id %d\n", id);
}