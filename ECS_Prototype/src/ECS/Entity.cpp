#include "Entity.h"

Entity::Entity() {
	m_componentMask = 0ULL;				// Unsigned Long Long	[64 bits]
	m_flagMask = ENTITYFLAGS::alive;	// Short				[16 bits]
										//  0	Is this entity alive?
}

Entity::~Entity() {

}