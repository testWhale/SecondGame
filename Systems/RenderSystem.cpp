#include "RenderSystem.hpp"
#include "../ECS/Coordinator.h"
#include "../Components/Transform.hpp"
#include "../shaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



extern Coordinator gCoordinator;

void RenderSystem::Init() {
	//what is mShape data.
	mShape = gCoordinator.CreateEntity();
	gCoordinator.AddComponent(
		mShape,
		Transform{
		glm::vec3(0.f,0.f,500.f)
		});
	//Projection Matrix

	

}

void RenderSystem::Update(float dt, Shader& shaderProgram) {

	//shaderProgram.use();
	//getComponents; Why? cus components are the effects u want to use every frame
	auto& ShapeTransform = gCoordinator.GetComponent<Transform>(mShape);


	glm::mat4 model2 = glm::mat4(1.0f);
	model2 = glm::translate(model2, { 0,0,0 });
	float angle2 = 0.f;
	model2 = glm::rotate(model2, glm::radians(angle2), glm::vec3(1.0f, 0.3f, 0.5f));

	shaderProgram.setMat4("model", model2);
	



}