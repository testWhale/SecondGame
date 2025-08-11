//GrFragColor = texture(textureUni0, TexCoord);

//#include<iostream>
//#include<glad/glad.h>
//#include<GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include"shaderClass.h"
//#include"VAO.h"
//#include"VBO.h"
//#include"EBO.h"
//#include"tex.h"
//#include "stb/stb_image.h"
//
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// Vertices coordinates
//float vertices[] = {
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//};
//
////// Indices for vertices order
////GLuint indices[] =
////{
////	0, 2, 1, // Upper triangle
////	0, 3, 2 // Lower triangle
////};
//
//
//
//int main()
//{
//	// Initialize GLFW
//	glfwInit();
//
//	// Tell GLFW what version of OpenGL we are using 
//	// In this case we are using OpenGL 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// Tell GLFW we are using the CORE profile
//	// So that means we only have the modern functions
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
//	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
//	// Error check if the window fails to create
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	// Introduce the window into the current context
//	glfwMakeContextCurrent(window);
//	
//	//Load GLAD so it configures OpenGL
//	gladLoadGL();
//	// Specify the viewport of OpenGL in the Window
//	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
//	glViewport(0, 0, 800, 800);
//
//
//
//	// Generates Shader object using shaders defualt.vert and default.frag
//	Shader shaderProgram("default.vert", "default.frag");
//
//	// Generates Vertex Array Object and binds it
//	VAO VAO1;
//	VAO1.Bind();
//
//	// Generates Vertex Buffer Object and links it to vertices
//	VBO VBO1(vertices, sizeof(vertices));
//	// Generates Element Buffer Object and links it to indices
//	//EBO EBO1(indices, sizeof(indices));
//
//	// Links VBO attributes such as coordinates and colors to VAO
//	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
//	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	// Unbind all to prevent accidentally modifying them
//	VAO1.Unbind();
//	VBO1.Unbind();
//	/*EBO1.Unbind();*/
//
//	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
//	glEnable(GL_DEPTH_TEST);
//
//	Texture texture0("container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
//	texture0.texUnit(shaderProgram, "textureUni0", 0);
//	float last = 0.f;
//	// Main while loop
//	char title[128];
//	glm::mat4 view;
//	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//
//	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//
//	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
//
//	//view = glm::lookAt(glm::vec3(cameraPos),
//	//	glm::vec3(cameraTarget),
//	//	glm::vec3(up));
//	const float radius = 10.0f;
//	float camX = sin(glfwGetTime()) * radius;
//	float camZ = cos(glfwGetTime()) * radius;
//	glm::mat4 view;
//
//
//	while (!glfwWindowShouldClose(window))
//	{
//
//
//		//how did i get the frame rate from 1.f/delta?
//		float now = glfwGetTime();
//		float delta = now - last;
//		last = now;
//		snprintf(title, 128,"YoutubeOpenGL - Delta Time: %f", 1.f/ delta);
//		glfwSetWindowTitle(window, title);
//
//
//		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//
//		// Specify the color of the background
//		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//		// Clean the back buffer and assign the new color to it
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		//model matrix -> world space
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//		// view matrix -> camera space
//		glm::mat4 view = glm::mat4(1.0f);
//		// translating the scene reverse direction
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//
//		// projection matrix (fustrum) -> clip space
//		glm::mat4 projection;
//		// fustrum angle, aspect ratio, near plane, far plane
//		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		int proLoc = glGetUniformLocation(shaderProgram.ID, "projection");
//		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		// clipspace -> screen coordinates
//
//
//		// Tell OpenGL which Shader Program we want to use
//		shaderProgram.use();
//		// Set the uniform Texture value
//		texture0.Bind();
//		// Set the uniform scale value
//		glUniform1f(uniID, 0.5f);
//
//
//		// Bind the VAO so OpenGL knows to use it
//		VAO1.Bind();
//		// Draw primitives, number of indices, datatype of indices, index of indices
//		glDrawArrays(GL_TRIANGLES, 0, 36); 
//		// Swap the back buffer with the front buffer
//		glfwSwapBuffers(window);
//		// Take care of all GLFW events
//		glfwPollEvents();
//	}
//
//
//
//	// Delete all the objects we've created
//	VAO1.Delete();
//	VBO1.Delete();
//	//EBO1.Delete();
//	texture0.Delete();
//	shaderProgram.Delete();
//	// Delete window before ending the program
//	glfwDestroyWindow(window);
//	// Terminate GLFW before ending the program
//	glfwTerminate();
//	return 0;
//}