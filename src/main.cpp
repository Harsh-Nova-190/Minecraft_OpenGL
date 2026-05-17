#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/Shader.h"
#include "camera/Camera.h"
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
using namespace std;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


// mouse settings
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 640.0f;
float lastY = 360.0f;
bool firstMouse = true;

//cube generation
const int  terrainWidth = 20;
const int  terrainDepth = 20;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	//float cameraSpeed = 2.5f * deltaTime;

	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	cameraPos += cameraSpeed * cameraFront;
	//}

	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	cameraPos -= cameraSpeed * cameraFront;
	//}

	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	//}

	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	//}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = (float)xpos;
//		lastY = (float)ypos;
//
//		firstMouse = false;
//	}
//
//	float xoffset = (float)xpos - lastX;
//	float yoffset = lastY - (float)ypos;
//
//	lastX = (float)xpos;
//	lastY = (float)ypos;
//
//	float sensitivity = 0.1f;
//
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	if (pitch > 89.0f)
//	{
//		pitch = 89.0f;
//	}
//	if (pitch < -89.0f)
//	{
//		pitch = -89.0f;
//	}
//
//	glm::vec3 direction;
//
//	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	direction.y = sin(glm::radians(pitch));
//	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//	cameraFront = glm::normalize(direction);
//}

int main()
{

	cout << filesystem::current_path() << endl;

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


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";

		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 1280, 720);

	Camera camera;

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float vertices[] =
	{
		// positions          // texture coords

		// Front
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		// Back
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,

		// Left
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

		// Right
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		 // Top
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

		 // Bottom
		 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,

		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f
	};


	unsigned int VBO;
	unsigned int VAO;
	unsigned int texture;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenTextures(1, &texture);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glEnableVertexAttribArray(1);

	int width;
	int height;
	int nrChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data =
		stbi_load("textures/Dirt.png",
			&width,
			&height,
			&nrChannels,
			0);

	if (data)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data
		);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

	Shader shader("shaders/triangle.vert", "shaders/triangle.frag");


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glBindTexture(GL_TEXTURE_2D, texture);

		processInput(window);
		
		
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
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3((float)x, 0.0f, (float)z));
				shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}


		glBindVertexArray(VAO);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);

	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}