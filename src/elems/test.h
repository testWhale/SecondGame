#ifndef CAMERA_H
#define CAMERA_H

#include "../pch.h"
#include "player.h"
enum Camera_Movement {
	FOR,
	BACK,
	LE,
	RI
};
// default mouse cam
const float YAW = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f; //fov

// the basics cam moves with = position + direction vec + up vec
// so whenever we move the camera, we need to update the position, up and direction vectors
// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	float distanceBack = 10.0f;
	float heightOffset = 6.0f;
	float sideOffset = 0.0f;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	//// the pitch, yaw, roll constructor. (nds the direction faced)
	//Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	//{
	//	Position = glm::vec3(posX, posY, posZ);
	//	WorldUp = glm::vec3(upX, upY, upZ);
	//	Yaw = yaw;
	//	Pitch = pitch;
	//	updateCameraVectors();
	//}
	/* bcs the view mat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)
	 we nd to returns the view matrix calculated using Euler Angles and the LookAt Matrix*/
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}
	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	/*void ProcessKeyboard(Camera_Movement direction, float delta)
	{
		float velocity = MovementSpeed * delta;
		if (direction == FOR) {
			Position += Front * velocity;
		}
		if (direction == BACK)
			Position -= Front * velocity;
		if (direction == LE)
			Position -= Right * velocity;
		if (direction == RI)
			Position += Right * velocity;
	}*/
	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	//void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	//{
	//	xoffset *= MouseSensitivity;
	//	yoffset *= MouseSensitivity;
	//	Yaw += xoffset;
	//	Pitch += yoffset;

	//	// make sure that when pitch is out of bounds, screen doesn't get flipped
	//	if (constrainPitch)
	//	{
	//		if (Pitch > 89.0f)
	//			Pitch = 89.0f;
	//		if (Pitch < -89.0f)
	//			Pitch = -89.0f;
	//	}

	//	// update Front, Right and Up Vectors using the updated Euler angles
	//	updateCameraVectors();
	//}

	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}
	void followPlayer(const glm::vec3& playerPos, const glm::vec3& playerFront, const glm::vec3& playerRight) {
		// Calculate behind position using player's front
		glm::vec3 offset = -(playerFront) * distanceBack + glm::vec3(0.0f, heightOffset, 0.0f) + playerRight * sideOffset;

		Position = offset + playerPos;
		Front = glm::normalize(playerPos - Position); // look at player
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front)); // or compute if needed

	}

private:
	// calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
#endif
