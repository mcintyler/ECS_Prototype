#pragma once

namespace ENTITYFLAGS {
	const unsigned short alive = 1 << 0;
}

class Entity {
public:
	unsigned long long m_componentMask;
	unsigned short m_flagMask;

	Entity();
	~Entity();
};