////Third-Parties
//#include <random>
//#include <fstream>
//#include <strstream>
//#include <vector>
//#include <iostream>
//#include <filesystem>
//#include <memory>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb/stb_image.h"
//#include <iostream>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
////Source Files
//#include "filesystem.h"
//#include "Model.h"
//#include "shaderClass.h"
//#include "camera.h"
//#include "VAO.h"
//#include "VBO.h"
//#include "EBO.h"
//#include "InputHandler.h"
//#include "actions.h"
//#include "player.h"
//
//
//
////Components
//#include "../ECS/Coordinator.h"
//#include "../Components/Gravity.hpp"
//#include "../Components/Thrust.hpp"
//#include "../Components/Transform.hpp"
//#include "../Components/RigidBody.hpp"
//
////Systems
//#include "../Systems/PhysicsSystem.hpp"
//
//
//#define GLM_ENABLE_EXPERIMENTAL
//
//struct GameContext {
//	Player* Player;
//	Camera* Camera;
//};
//Coordinator gCoordinator;
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
////how did i get the frame rate from 1.f/delta?
//float delta = 0.f;
//// timing
////float delta = 0.0f;	// time between current frame and last frame
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
////void processInput(GLFWwindow* window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//unsigned int loadTexture(const char* path);
//void applyLightingUniforms(Shader& shader, const Camera& camera);
//
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//int main()
//{
//#if defined(__cplusplus)
//	// Output the version of C++
//	std::cout << "C++ version: " << __cplusplus << std::endl;
//#else
//	// Notify that the version could not be detected
//	std::cout << "C++ version could not be determined." << std::endl;
//#endif
//
//	// This outputs the versions of the GCC or Clang compiler, if applicable
//#ifdef __GNUC__
//	std::cout << "GCC version : " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
//#endif
//
//#ifdef __clang__
//	std::cout << "Clang version : " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << std::endl;
//#endif
//
//	// Output the Microsoft Visual C++ compiler version, if applicable
//#ifdef _MSC_VER
//	std::cout << "MSVC version : " << _MSC_VER << std::endl;
//#endif
//
//	//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
//	// Initialize GLFW
//	glfwInit();
//	// Tell GLFW what version of OpenGL we are using 
//	// In this case we are using OpenGL 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// Tell GLFW we are using the CORE profile
//	// So that means we only have the modern functions
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//***-------------------***
//	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
//	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
//	// Error check if the window fails to create
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	// the GPU def framebuffer: creates a Frame buffer n color attachment
//	// stores colors, from frag-shader. into it 
//	// enables depth in depth buffer
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	InputHandler inputHandler(window);
//
//	//Load GLAD so it configures OpenGL
//	gladLoadGL();
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// configure global opengl state 
//	//***-------------------***
//	glEnable(GL_DEPTH_TEST);
//	// Specify the viewport of OpenGL in the Window
//	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
//	glViewport(0, 0, 800, 800);
//
//	// Generates Shader object using shaders defualt.vert and default.frag
//	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");
//	Shader lightCubeShader("Shaders/light_cube.vs", "Shaders/light_cube.fs");
//	Shader rockShader("Shaders/instancing.vert", "Shaders/instance.frag");
//
//	Player player(FileSystem::getPath("assets/player/player.obj"), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f));
//	GameContext gameContext;
//	gameContext.Camera = &camera;
//	gameContext.Player = &player;
//	float vertices[] = {
//		// positions          // normals           // texture coords
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//	};
//	glm::vec3 cubePositions[] = {
//	glm::vec3(0.0f,  0.0f,  0.0f),
//	glm::vec3(2.0f,  5.0f, -15.0f),
//	glm::vec3(-1.5f, -2.2f, -2.5f),
//	glm::vec3(-3.8f, -2.0f, -12.3f),
//	glm::vec3(2.4f, -0.4f, -3.5f),
//	glm::vec3(-1.7f,  3.0f, -7.5f),
//	glm::vec3(1.3f, -2.0f, -2.5f),
//	glm::vec3(1.5f,  2.0f, -2.5f),
//	glm::vec3(1.5f,  0.2f, -1.5f),
//	glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//	//
//		//
//		// Indices for vertices order
//	GLuint indices[] =
//	{
//		0, 2, 1, // Upper triangle
//		0, 3, 2 // Lower triangle
//	};
//	float floorVertices[] = {
//		// positions            // normals        // texcoords
//		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
//		 10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
//		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f, 10.0f, 10.0f,
//
//		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f, 10.0f, 10.0f,
//		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  0.0f, 10.0f,
//		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f
//	};
//
//
//
//
//
//
//
//	//Model ourModel("obj/spaceship_3.fbx");
//	// Generates Vertex Array Object and binds it
//	VAO VAO1;
//	VAO1.Bind();
//	//// Generates Vertex Buffer Object and links it to vertices
//	VBO VBO1(vertices, sizeof(vertices));
//	//// Generates Element Buffer Object and links it to indices
//	////EBO EBO1(indices, sizeof(indices));
//	// Links VBO attributes such as coordinates and colors to VAO
//	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(0);
//	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	//VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	//glEnableVertexAttribArray(1);
//	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	//BY DEF THIS FDS data into the vert shader
//	// Unbind all to prevent accidentally modifying them
//	VAO1.Unbind();
//	VBO1.Unbind();
//	//unsigned int diffuseMap = loadTexture(FileSystem::getPath("resources/textures/container2.png").c_str());
//	//shaderProgram.use();
//	//shaderProgram.setInt("material.diffuse", 0);
//	/*EBO1.Unbind();*/
//	VAO floorVAO;
//	VBO VBO2(floorVertices, sizeof(floorVertices));
//	floorVAO.Bind();
//	floorVAO.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
//	floorVAO.LinkAttrib(VBO2, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	floorVAO.LinkAttrib(VBO2, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
//	floorVAO.Unbind();
//	VBO2.Unbind();
//
//	VAO lightVAO;
//	lightVAO.Bind();
//	lightVAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(0);
//	lightVAO.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	//VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	//glEnableVertexAttribArray(1);
//	lightVAO.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
//	lightVAO.Unbind();
//
//	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
//	glEnable(GL_DEPTH_TEST);
//	// Bind to same point 0
//		//Texture texture3("container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
//		//texture3.texUnit(shaderProgram, "textureUni3", 0);
//		//Texture conSpec("container_specmap.JPG", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
//		//conSpec.texUnit(shaderProgram, "textureUni1", 1);
//	unsigned int diffuseMap = loadTexture(FileSystem::getPath("Textures/container2.png").c_str());
//	unsigned int specMap = loadTexture(FileSystem::getPath("Textures/container2_specular.png").c_str());
//	shaderProgram.use();
//	shaderProgram.setInt("material.diffuse", 0);
//	shaderProgram.setInt("material.specular", 1);
//
//	// Load model
//	//Model ourModel(FileSystem::getPath("assets/backpack.obj"));
//	//ourModel.position = glm::vec3(10, 10, 0);
//
//	inputHandler.setWCmd(new WCmd(&player, &delta));
//	inputHandler.setACmd(new ACmd(&player, &delta));
//	inputHandler.setSCmd(new SCmd(&player, &delta));
//	inputHandler.setDCmd(new DCmd(&player, &delta));
//
//
//
//
//	////ECS SYSTEM
//	//gCoordinator.Init();
//	//gCoordinator.RegisterComponent<Gravity>();
//	//gCoordinator.RegisterComponent<RigidBody>();
//	//gCoordinator.RegisterComponent<Thrust>();
//	//gCoordinator.RegisterComponent<Transform>();
//
//	////De control systems
//	//auto physicsSystem = gCoordinator.RegisterSystem<PhysicsSystem>();
//	//{
//	//	//set signature to Components
//	//	Signature signature;
//	//	signature.set(gCoordinator.GetComponentType<Gravity>());
//	//	signature.set(gCoordinator.GetComponentType<RigidBody>());
//	//	signature.set(gCoordinator.GetComponentType<Transform>());
//	//	gCoordinator.SetSystemSignature<PhysicsSystem>(signature);
//	//}
//	//physicsSystem->Init();
//
//	//std::vector<Entity> entities(MAX_ENTITIES);
//
//	//std::default_random_engine generator;
//	//std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
//	//std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
//	//std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
//	//std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);
//	//float scale = randScale(generator);
//	//for (auto& entity : entities)
//	//{
//	//	entity = gCoordinator.CreateEntity();
//
//	//	gCoordinator.AddComponent(
//	//		entity,
//	//		Gravity{ glm::vec3(0.0f, randGravity(generator), 0.0f) });
//
//	//	gCoordinator.AddComponent(
//	//		entity,
//	//		RigidBody{
//	//			glm::vec3(0.0f, 0.0f, 0.0f),
//	//			glm::vec3(0.0f, 0.0f, 0.0f)
//	//		});
//
//	//	gCoordinator.AddComponent(
//	//		entity,
//	//		Transform{
//	//			glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
//	//			glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
//	//			glm::vec3(scale, scale, scale)
//	//		});
//	//}
//
//	///=================
//	//----METEOR CODE----
//	Shader trial("./Shaders/trial.vert", "./Shaders/trial.frag");
//	glm::vec2 translations[100];
//	int index = 0;
//	float offsetT = 0.1f;
//	for (int y = -10; y < 10; y += 2)
//	{
//		for (int x = -10; x < 10; x += 2)
//		{
//			glm::vec2 translation;
//			translation.x = (float)x / 10.0f + offsetT;
//			translation.y = (float)y / 10.0f + offsetT;
//			translations[index++] = translation;
//		}
//	}
//
//
//	unsigned int instanceVBO;
//	glGenBuffers(1, &instanceVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	float quadVertices[] = {
//		// positions     // colors
//		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
//
//		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//		 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
//	};
//	unsigned int quadVAO, quadVBO;
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//
//	//instance comes from a diff buffer so need to rebind
//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glVertexAttribDivisor(2, 1); //tells OpenGL every 2 instances, update instanced vertex attribute [i]
//
//	Model rock("./assets/rock/rock.obj");
//
//	//Gen Random Transfroms per instance
//	unsigned int amount = 10000;
//	glm::mat4* modelMatrices;
//	modelMatrices = new glm::mat4[amount];
//	srand(glfwGetTime()); // initialize random seed	
//	float radius = 50.0;
//	float offset = 25.0f;
//	for (unsigned int i = 0; i < amount; i++)
//	{
//		glm::mat4 model = glm::mat4(1.0f);
//		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
//		float angle = (float)i / (float)amount * 360.0f;
//		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float x = sin(angle) * radius + displacement;
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float z = cos(angle) * radius + displacement;
//		model = glm::translate(model, glm::vec3(x, y, z));
//
//		// 2. scale: scale between 0.05 and 0.25f
//		float scale = (rand() % 20) / 100.0 + 0.05;
//		model = glm::scale(model, glm::vec3(scale));
//
//		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
//		float rotAngle = (rand() % 360);
//		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//
//		// 4. now add to list of matrices
//		modelMatrices[i] = model;
//		/*std::cout << modelMatrices << std::endl;*/
//	}
//	// vertex buffer object
//	unsigned int bufferV;
//	glGenBuffers(1, &bufferV);
//	glBindBuffer(GL_ARRAY_BUFFER, bufferV);
//	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
//
//	for (unsigned int i = 0; i < rock.meshes.size(); i++)
//	{
//		glBindVertexArray(rock.meshes[i].VAO);
//		glBindBuffer(GL_ARRAY_BUFFER, bufferV);
//		// vertex attributes
//		std::size_t vec4Size = sizeof(glm::vec4);
//		glEnableVertexAttribArray(3);
//		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
//		glEnableVertexAttribArray(4);
//		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
//		glEnableVertexAttribArray(5);
//		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
//		glEnableVertexAttribArray(6);
//		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
//
//		glVertexAttribDivisor(3, 1);
//		glVertexAttribDivisor(4, 1);
//		glVertexAttribDivisor(5, 1);
//		glVertexAttribDivisor(6, 1);
//
//		glBindVertexArray(0);
//	}
//
//	// Must match binding point used in glBindBufferBase
//	   // Fill lighting.lightPos, ambient, etc.
//
//
//
//	   ///=================
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	float last = 0.f;
//	char title[128];
//	double currentMouseX, currentMouseY;
//	double lastMouseX = 0.0;
//	double lastMouseY = 0.0;
//	while (!glfwWindowShouldClose(window))
//	{
//		//per-frame logic
//		float now = glfwGetTime();
//		delta = now - last;
//		last = now;
//		//title
//		snprintf(title, 128, "YoutubeOpenGL - Delta Time: %f", 1.f / delta);
//		glfwSetWindowTitle(window, title);
//		//physicsSystem->Update(delta);
//		// Process all input
//		inputHandler.processInput();
//		// Specify the color of the background
//		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//		// Clean the back buffer and assign the new color to it
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glEnable(GL_DEPTH_TEST);
//		//glfwGetCursorPos(window, &currentMouseX, &currentMouseY);
//
//
//			// draw meteorites
//
//
//		// counter-clockwise winding order
//		shaderProgram.use();
//
//		player.Draw(shaderProgram);
//
//
//		glfwSetCursorPosCallback(window, mouse_callback);
//		glfwSetWindowUserPointer(window, &gameContext);
//
//		//shaderProgram.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
//		//shaderProgram.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f); //this messes the color?
//		shaderProgram.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
//		shaderProgram.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
//		shaderProgram.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//		shaderProgram.setFloat("light.constant", 1.0f);
//		shaderProgram.setFloat("light.linear", 0.09f);
//		shaderProgram.setFloat("light.quadratic", 0.032f);
//		// material 
//		//shaderProgram.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//		shaderProgram.setFloat("material.shininess", 64.0f);
//		shaderProgram.setVec3("light.position", camera.Position);
//		shaderProgram.setVec3("light.direction", camera.Front);
//
//		shaderProgram.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
//		shaderProgram.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
//
//		camera.followPlayer(player.position, player.Front, player.Right);
//
//		//model matrix -> world space
//		glm::mat4 model = glm::mat4(1.0f);
//		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
//		shaderProgram.setMat4("model", model);
//		shaderProgram.setMat3("normalMat", normalMatrix);
//		//model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//		// bind diffuse map
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, specMap);
//
//		// translating the scene reverse direction
//		const float radius = 10.0f;
//		float camX = sin(glfwGetTime()) * radius;
//		float camZ = cos(glfwGetTime()) * radius;
//
//		// view matrix -> camera space
//		// camera/view transformation
//		glm::mat4 view = camera.GetViewMatrix();
//		//shaderProgram.setMat4("view", view);
//		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//
//		// projection matrix (fustrum) -> clip space
//		glm::mat4 projection;
//		// fustrum angle, aspect ratio, near plane, far plane
//		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		int proLoc = glGetUniformLocation(shaderProgram.ID, "projection");
//		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));
//		// clipspace -> screen coordinates
//		// Tell OpenGL which Shader Program we want to use
//
//		// Set the uniform Texture value
//	/*	texture0.Bind();
//		conSpec.Bind();*/
//
//		// Set the uniform scale value
//		glUniform1f(uniID, 0.5f);
//		/*int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));*/
//		// Bind the first cube so OpenGL knows to use it
//		VAO1.Bind();
//		// Draw primitives, number of indices, datatype of indices, index of indices
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		//FLOOR
//		glm::mat4 model2 = glm::mat4(1.0f);
//		model2 = glm::translate(model2, { 0,0,0 });
//		float angle2 = 0.f;
//		model2 = glm::rotate(model2, glm::radians(angle2), glm::vec3(1.0f, 0.3f, 0.5f));
//		shaderProgram.setMat4("model", model2);
//		floorVAO.Bind();
//		// no1: starting index (get by {no. of faces} * {no. of vertices}) 
//		// no2: no. of vertices
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		//shaderProgram.setMat4("model",ourModel.getModelMatrix());
//		//ourModel.Draw(shaderProgram);
//// Test draw
//		rockShader.use();
//		//glm::mat4 identity = glm::mat4(1.0f);
//		rockShader.setMat4("projection", projection);
//		rockShader.setMat4("view", view);
//
//		//glm::mat4 testMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
//		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(testMat)); //replce all modelMatrices with testMat
//		//rockShader.setMat4("model", identity); // if you're using aInstanceMatrix directly
//		for (unsigned int i = 0; i < rock.meshes.size(); i++) { //Looping through all meshes of rock.
//			glBindVertexArray(rock.meshes[i].VAO);
//			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
//
//		}
//
//
//
//
//
//
//
//		//trial.use();
//		//glBindVertexArray(quadVAO);
//		//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
//		//glBindVertexArray(0);
//
//		/*for (unsigned int i = 0; i < 10; i++) {
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//
//			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			shaderProgram.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}*/
//
//
//		//// draw meteorites
//		//instanceShader.use();
//		//instanceShader.setMat4("projection", projection);
//		//instanceShader.setMat4("view", view);
//		//instanceShader.setInt("texture_diffuse1", 0);
//
//		//glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id);
//		////rock.meshes[10].Draw(instanceShader);
//
//		//glActiveTexture(GL_TEXTURE0); //its ok to reuse tex unit 0, only add GL_TEX2 if using multiple textures in one shader for an obj: eg. Diffuse Spec maps.
//		//glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); //this says bind sampler(texture_diffuse1) to tex unit 0
//		//for (unsigned int i = 0; i < rock.meshes.size(); i++)
//		//{
//		//	//std::cout << rock.meshes.size() << std::endl;
//		//	glBindVertexArray(rock.meshes[i].VAO);
//		//	glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(rock.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
//		//	glBindVertexArray(0);
//		//}
//
//		//// also draw the lamp object
//		lightCubeShader.use();
//		lightCubeShader.setMat4("projection", projection);
//		lightCubeShader.setMat4("view", view);
//
//		glm::mat4 modelLight = glm::mat4(1.0f);
//		modelLight = glm::translate(modelLight, lightPos);
//		float angle = 20.0f * 9;
//		modelLight = glm::rotate(modelLight, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//		modelLight = glm::scale(modelLight, glm::vec3(0.2f)); // a smaller cube
//		lightCubeShader.setMat4("model", modelLight);
//		lightVAO.Bind();
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		// Swap the back buffer with the front buffer
//		glfwSwapBuffers(window);
//		// Take care of all GLFW events
//		glfwPollEvents();
//	}
//
//	// Delete all the objects we've created
//	VAO1.Delete();
//	lightVAO.Delete();
//	VBO1.Delete();
//	floorVAO.Delete();
//	VBO2.Delete();
//	VBO1.Delete();
//	glDeleteVertexArrays(1, &quadVAO);
//	glDeleteBuffers(1, &quadVBO);
//	/*texture0.Delete();*/
//	//EBO1.Delete();
//	//texture0.Delete();
//	shaderProgram.Delete();
//	lightCubeShader.Delete();
//	// Delete window before ending the program
//	glfwDestroyWindow(window);
//	// Terminate GLFW before ending the program
//	glfwTerminate();
//	return 0;
//}
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//	float xpos = static_cast<float>(xposIn);
//	float ypos = static_cast<float>(yposIn);
//	GameContext* gameContext = static_cast<GameContext*>(glfwGetWindowUserPointer(window));
//	if (!gameContext) return;
//
//	Player* player = gameContext->Player;
//	Camera* camera = gameContext->Camera;
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//
//	player->ProcessMouseMovement(-xoffset, yoffset);
//	camera->followPlayer(player->position, player->Front, player->Right);
//
//}
//void applyLightingUniforms(Shader& shader, const Camera& camera)
//{
//	shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
//	shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
//	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//	shader.setFloat("light.constant", 1.0f);
//	shader.setFloat("light.linear", 0.09f);
//	shader.setFloat("light.quadratic", 0.032f);
//	shader.setVec3("light.position", camera.Position);
//	shader.setVec3("light.direction", camera.Front);
//	shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
//	shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
//}
////void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
////{
////	float xpos = static_cast<float>(xposIn);
////	float ypos = static_cast<float>(yposIn);
////
////	if (firstMouse)
////	{
////		lastX = xpos;
////		lastY = ypos;
////		firstMouse = false;
////	}
////
////	float xoffset = xpos - lastX;
////	float yoffset = lastY - ypos;
////	lastX = xpos;
////	lastY = ypos;
////
////	Player* player = static_cast<Player*>(glfwGetWindowUserPointer(window));
////	if (player)
////		player->ProcessMouseMovement((float)xoffset, (float)yoffset);
////}
//
////void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
////{
////	float xpos = static_cast<float>(xposIn);
////	float ypos = static_cast<float>(yposIn);
////
////	if (firstMouse)
////	{
////		lastX = xpos;
////		lastY = ypos;
////		firstMouse = false;
////	}
////
////	float xoffset = xpos - lastX;
////	float yoffset = lastY - ypos;
////	lastX = xpos;
////	lastY = ypos;
////
////	camera.ProcessMouseMovement(xoffset, yoffset);
////}
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
////void processInput(GLFWwindow* window)
////{
////	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
////		glfwSetWindowShouldClose(window, true);
////	
////	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
////		camera.ProcessKeyboard(FORWARD, delta);
////		/*std::cout << "W" << std::endl;*/
////	}
////	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
////		camera.ProcessKeyboard(BACKWARD, delta);
////		
////	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
////		camera.ProcessKeyboard(BACKWARD, delta);
////	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
////		camera.ProcessKeyboard(LEFT, delta);
////	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
////		camera.ProcessKeyboard(RIGHT, delta);
////}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//unsigned int loadTexture(char const* path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID); // <-- This initializes it
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data) {
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
