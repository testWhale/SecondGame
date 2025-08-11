#ifndef PLAYER_H
#define PLAYER_H
#include "../pch.h"
#include "../Model.h"
#include "../shaderClass.h"

#include <iostream>
enum CommandType {
MoveForward,
MoveBackward,
MoveLeft,
MoveRight,
JumpUp
};
enum Player_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	JUMP
};
const float SENSE = 0.1f;
const float YAW_P = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
const float PITCH_P = 0.0f;
const float gravity = -9.8;

class Player {
public:
	glm::vec3 position;
	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	glm::vec3 velocity;
	float speed, Yaw, Pitch, MouseSensitivity;
	Model model;
	bool onGround;
	bool firstMouse = true;
	float lastX = 400, lastY = 300;

	Player(const std::string& modelPath, glm::vec3 pos = glm::vec3(0.f), glm::vec3 vel = glm::vec3(0.f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW_P, float pitch = PITCH_P)
		: model(modelPath), position(pos), Front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(5.0f), Yaw(-90.0f), Pitch(0.0f), WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), velocity(vel), MouseSensitivity(SENSE) 
	{
		updatePlayerVectors();
	};
	//Delete Player Object
	//~Player(){
	// 
	// }
	//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn, Player& player)
	//{
	//	float xpos = static_cast<float>(xposIn);
	//	float ypos = static_cast<float>(yposIn);

	//	if (firstMouse)
	//	{
	//		lastX = xpos;
	//		lastY = ypos;
	//		firstMouse = false;
	//	}

	//	float xoffset = xpos - lastX;
	//	float yoffset = lastY - ypos;
	//	lastX = xpos;
	//	lastY = ypos;

	//	player.ProcessMouseMovement(xoffset, yoffset);
	//	camera.followPlayer(player.position, player.Front, player.Right);

	//}


	// Setters
	/*glm::vec3 getPlayerPos() const;*/
	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xpos, float ypos, GLboolean constrainPitch = true)
	{
		//if (firstMouse)
		//{
		//	lastX = xpos;
		//	lastY = ypos;
		//	firstMouse = false;
		//	return;
		//}
		float xoffset = xpos;
		float yoffset = ypos;
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;
		Yaw += xoffset;
		Pitch += yoffset;

		//// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}
		// update Front, Right and Up Vectors using the updated Euler angles
		updatePlayerVectors();
	}
	/*void rotateYaw(float angleOffset)
	{
		angleOffset = angleOffset * MouseSensitivity;
		Yaw += angleOffset;
		Front = glm::normalize(glm::vec3(
			cos(glm::radians(Yaw)),
			0.0f,
			sin(glm::radians(Yaw))
		));
	}*/

	// Your existing movement logic
	void ProcessKeyboard(Player_Movement direction, float delta)
	{
		float velocity = speed * delta;
		if (direction == FORWARD) {
			position += Front * velocity;
		}
		if (direction == BACKWARD)
			position -= Front * velocity;
		if (direction == LEFT)
			position -= Right * velocity;
		if (direction == RIGHT)
			position += Right * velocity;
	}
	

	float getGroundHeightAt(float x, float z) {
		return 0.0f; // flat terrain
	}
	float DebugYaw = 0.0f;
	void Draw(Shader& shader) {
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
		// Yaw = rotation around X-axis (left/right)
		//modelMatrix = glm::rotate(modelMatrix, glm::radians(260.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		DebugYaw += 1.0f;
		// Pitch = rotation around Y-axis (up/down)

		modelMatrix = glm::rotate(modelMatrix, glm::radians(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f)); // a smaller cube

		/*modelMatrix = glm::lookAt(position, position + Front, Up);*/
		shader.setMat4("model", modelMatrix);
		model.Draw(shader);
		//std::cout << "DebugYaw N: " << Yaw << std::endl;
	}


	//void HandleCommand(CommandType cmd);
	//void SetState(PlayerState& state);

	//void ChangeState(PlayerState& newState);

	//float* delta || delta = float address, delta* = value (pointer)
	// float& delta || delta =  float value (reference)
	//void Update(float& deltaTime);

private:
	//PlayerState* currentState = nullptr;
	// calculates the front vector from the Camera's (updated) Euler Angles
	void updatePlayerVectors()
	{
		glm::vec3 front;

		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
		//std::cout << "Yaw: " << Yaw << std::endl;
	}
};


//class ForwardState : public PlayerState {
//public:
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Jumping State\n";
//	}
//	void Update(Player& player, float& deltaTime) override {
//		/*player.velocity.y += gravity * deltaTime;*/
//		player.position += player.Front * player.velocity * deltaTime;
//	}
//private:
//};
//class BackwardState : public PlayerState {
//public:
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Jumping State\n";
//	}
//	void Update(Player& player, float& deltaTime) override {
//		/*player.velocity.y += gravity * deltaTime;*/
//		player.position -= player.Front * player.velocity * deltaTime;
//	}
//private:
//};
//class RightState : public PlayerState {
//public:
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Jumping State\n";
//	}
//	void Update(Player& player, float& deltaTime) override {
//		/*player.velocity.y += gravity * deltaTime;*/
//		player.position += player.Right * player.velocity * deltaTime;
//	}
//private:
//};
//class LeftState : public PlayerState {
//public:
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Jumping State\n";
//	}
//	void Update(Player& player, float& deltaTime) override {
//		/*player.velocity.y += gravity * deltaTime;*/
//		player.position -= player.Right * player.velocity * deltaTime;
//	}
//private:
//};


#endif
