#pragma once
#include "../ECS/System.h"

class PhysicsSystem : public System
{
public:
	void Init();
	void Update(float dt);
}; 