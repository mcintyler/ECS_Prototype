#pragma once

class ECS {
private:
	static ECS* m_instance;
	ECS();


public:
	~ECS();
	static ECS* GetInstance();

	bool Init();
};