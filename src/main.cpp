#include "engine/Core.h"
#include "graphics/Shader.h"
#include "camera/Camera.h"
#include "world/Block.h"
#include "engine/Window.h"

Camera camera;

// Terrain generation
const int  terrainWidth = 20;
const int  terrainDepth = 20;

// Delta time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);


int main()
{
	
	// Initialize engine/core
	Window window(1280, 720, "Minecraft Clone");

	if(!window.initialize())
	{
		return -1;
	}

	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glEnable(GL_DEPTH_TEST);

	Shader shader("shaders/triangle.vert", "shaders/triangle.frag");

	Block block;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	while (!window.shouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// camera movement
		camera.processKeyboardInput(window.getWindow(), deltaTime);
		
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
		
		window.swapBuffer();
		window.pollEvents();
	}

	window.shutdown();

	return 0;
}