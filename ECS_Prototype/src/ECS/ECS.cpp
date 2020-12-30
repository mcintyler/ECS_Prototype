#include "../DEFINITIONS.h"
#include "ECS.h"
#include <stdio.h>
#include <stdarg.h>

ECS* ECS::m_instance = nullptr;

ECS::ECS() {
	// Set minimum initial allocation size of entityPool
	m_entityPool.reserve(MinEntityPoolCapacity);
	printf("[ECS] MinEntityPoolCapacity = %d\n", MinEntityPoolCapacity);
}

ECS::~ECS() { }

ECS* ECS::GetInstance() {
	if(m_instance == nullptr) {
		m_instance = new ECS();
	}
	return m_instance;
}


bool ECS::Init(int totalComponents, ...) {
	// Initialize the static state of ComponentStore
	ComponentStore::offsets = (size_t*)malloc(totalComponents * sizeof(size_t));
	ComponentStore::sizes = (size_t*)malloc(totalComponents * sizeof(size_t));
	ComponentStore::type_count = totalComponents;

	// Calculate offsets and total data size of all components
	size_t total_size = 0;
	va_list vl;
	va_start(vl, totalComponents);
	for(int i = 0; i < totalComponents; i++) {
		size_t cSize = va_arg(vl, size_t);
		ComponentStore::sizes[i] = cSize;
		ComponentStore::offsets[i] = total_size;
		total_size += cSize;
	}
	va_end(vl);
	ComponentStore::total_size = total_size;

	return true;
}

void ECS::FreeComponentStore() {
	free(ComponentStore::offsets);
}

Entity* ECS::CreateEntity() {
	int eID = -1;

	if(m_deadEntityIDs.size() > 0) {
		// If available, use a dead entity's ID...
		eID = m_deadEntityIDs.back();
		m_deadEntityIDs.pop_back();
		// Replace dead entity data
		m_entityPool.at(eID) = Entity(eID);
	} else {
		// ...else use next unallocated entity ID
		eID = (int)m_entityPool.size();
		// Add new entity to the pool
		m_entityPool.push_back(Entity(eID));
	}

	printf("[ECS] Created new Entity with id %d\n", eID);
	return &m_entityPool.at(eID);
}

void ECS::KillEntity(int eID) {
	if(eID >= m_entityPool.size()) {
		printf("[ECS] Couldn't kill Entity with id %d, id %d out of range\n", eID, eID);
	}

	// Clear all flags (including the isAlive flag to free this entity for future use)
	m_entityPool.at(eID).m_flags.reset();
	// Remove all components
	m_entityPool.at(eID).ClearComponents();
	// Add id to list of dead IDs
	m_deadEntityIDs.push_back(eID);

	printf("[ECS] Killed Entity with id %d\n", eID);
}