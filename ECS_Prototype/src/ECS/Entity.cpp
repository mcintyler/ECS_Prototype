#include "Entity.h"

Entity::Entity(int eID) {
	m_eID = eID;
	// Set isAlive flag to true by default
	m_flags.set(EntityFlags::IS_ALIVE, 1);
	// Allocate memory for the component data
	m_componentStore.data = malloc(ComponentStore::total_size);
	memset(m_componentStore.data, 0, ComponentStore::total_size);
}

Entity::~Entity() {
	// Free memory for the component data
	free(m_componentStore.data);
}

void Entity::AddComponent(ComponentID cID, void* data) {
	if(cID < 0 || cID >= MaxComponents) {
		printf("[ECS] Failed to add component %d to entity %d, id %d is out of range\n", cID, m_eID, m_eID);
		return;
	}
	if(data == nullptr) {
		printf("[ECS] Failed to add component %d to entity %d, data is nullptr\n");
		return;
	}

	// Find the offset position of this component's data
	size_t offset = ComponentStore::offsets[cID];
	// Copy the component data into the component store
	void* ptr = &m_componentStore.data + offset;
	memcpy(ptr, data, ComponentStore::sizes[cID]);
	// Update component flags
	m_componentMask.set(cID, 1);
}

void Entity::RemoveComponent(ComponentID cID) {
	if(cID < 0 || cID >= MaxComponents) {
		printf("[ECS] Failed to remove component %d from entity %d, id %d is out of range\n", cID, m_eID, m_eID);
		return;
	}
	if(m_componentMask.test(cID) == 0) {
		printf("[ECS] Failed to remove component %d from entity %d, entity doesn't have component %d\n", cID, m_eID, cID);
		return;
	}

	// Find the offset position of this component's data
	size_t offset = ComponentStore::offsets[cID];
	// Clear the component data in the component store
	void* ptr = &m_componentStore.data + offset;
	memset(ptr, 0, ComponentStore::sizes[cID]);
	// Update component flags
	m_componentMask.set(cID, 0);
}

void Entity::ClearComponents() {
	// Reset data
	memset(&m_componentStore.data, 0, ComponentStore::total_size);
	// Reset component mask
	m_componentMask.reset();
}

void* Entity::GetComponent(ComponentID cID) {
	if(cID < 0 || cID >= MaxComponents) {
		printf("[ECS] Failed to get component %d from entity %d, id %d is out of range\n", cID, m_eID, m_eID);
		return nullptr;
	}
	if(m_componentMask.test(cID) == 0) {
		printf("[ECS] Failed to get component %d from entity %d, entity doesn't have component %d\n", cID, m_eID, cID);
		return nullptr;
	}

	// Find the pointer to this component's data
	size_t offset = ComponentStore::offsets[cID];
	void* ptr = &m_componentStore.data + offset;

	return ptr;
}
