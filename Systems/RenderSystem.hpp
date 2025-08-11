#pragma once
#include "../ECS/System.h"
#include "../shaderClass.h"


class RenderSystem : public System {
public:
	//Intaitionlization list

	//functions
	void Init();
	void Update(float dt, Shader& shaderProgram);
private:
	Entity mCamera;
	Entity mShape;

	

};