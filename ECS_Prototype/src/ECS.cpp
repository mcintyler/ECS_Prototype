#include "ECS.h"

ECS* ECS::m_instance = nullptr;

ECS::ECS() {

}

ECS::~ECS() {

}

ECS* ECS::GetInstance() {
	if(m_instance == nullptr) {
		m_instance = new ECS();
	}
	return m_instance;
}

bool ECS::Init() {
	return true;
}