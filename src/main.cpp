#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "graphics/Shader.h"
#include "camera/Camera.h"
#include "world/Block.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 640.0f;
float lastY = 360.0f;
bool firstMouse = true;

Camera camera;

//cube generation
const int  terrainWidth = 20;
const int  terrainDepth = 20;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.processMouseMovement(xoffset, yoffset);
}

int main()
{

	std::cout << std::filesystem::current_path() << std::endl;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(1280, 720, "Minecraft Clone", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window\n";

		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";

		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Block block;

	glViewport(0, 0, 1280, 720);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader shader("shaders/triangle.vert", "shaders/triangle.frag");


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.moveForward(deltaTime);
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.moveBackward(deltaTime);
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.moveLeft(deltaTime);
		}
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.moveRight(deltaTime);
		}
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		
		
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = camera.getProjectionMatrix(1280.0f / 720.0f);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		for (int x = 0; x < terrainWidth; x++)
		{
			for (int z = 0; z < terrainDepth; z++)
			{
				block.draw(shader, glm::vec3(
					(float)x - terrainWidth / 2.0f,
					0.0f,
					(float)z - terrainDepth / 2.0f));
			}
		}


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}