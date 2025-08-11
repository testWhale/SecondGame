#include "PhysicsSystem.hpp"
#include "../ECS/Coordinator.h"
#include "../Components/RigidBody.hpp"
#include "../Components/Thrust.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Gravity.hpp"

extern Coordinator gCoordinator;

void PhysicsSystem::Init() {
	std::cout << "CHICK" << endl;
}
void PhysicsSystem::Update(float dt) {
	for (auto const& entity : mEntities) {
		auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
		auto& gravity = gCoordinator.GetComponent<Gravity>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

		transform.position += rigidBody.velocity + dt;
		rigidBody.velocity += gravity.force + dt;

	}
}