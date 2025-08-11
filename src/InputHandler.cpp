#include "InputHandler.h"

InputHandler::InputHandler(GLFWwindow* window) : window(window), buttonW(nullptr), buttonS(nullptr), buttonA(nullptr), buttonD(nullptr), spaceBar(nullptr), clickLeft(nullptr) {}
InputHandler::~InputHandler() {
	delete spaceBar;
	delete buttonW;
	delete buttonA;
	delete buttonS;
	delete buttonD;
	delete clickLeft;
}

void InputHandler::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
		buttonW->execute();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
		buttonS->execute();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
		buttonA->execute();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
		buttonD->execute();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		spaceBar->execute();
}

void InputHandler::setWCmd(Command* command) {
	buttonW = command;
}
void InputHandler::setACmd(Command* command) {
	buttonA = command;
}
void InputHandler::setSCmd(Command* command) {
	buttonS = command;
}
void InputHandler::setDCmd(Command* command) {
	buttonD = command;
}
void InputHandler::setSpaceBarCmd(Command* command) {
	spaceBar = command;
}
void InputHandler::setClickLeftCmd(Command* command) {
	clickLeft = command;
}
