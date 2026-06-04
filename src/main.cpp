#include "engine/Core.h"
#include "graphics/Shader.h"
#include "camera/Camera.h"
#include "world/Block.h"
#include "engine/Window.h"
#include "world/World.h"
#include "renderer/WorldRenderer.h"
#include "renderer/BlockRenderer.h"

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

	World world;

	std::cout << world.chunkManager.getChunks().size() << std::endl;
	
	// Initialize engine/core
	Window window(1280, 720, "Minecraft Clone");

	if(!window.initialize())
	{
		return -1;
	}

	BlockRenderer blockRenderer;
	WorldRenderer renderer(blockRenderer);

	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!window.shouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// camera movement
		camera.processKeyboardInput(window.getWindow(), deltaTime);

		world.chunkManager.update(camera.getPosition());

		std::string title = "Minecraft Clone | X: " + std::to_string(camera.getPosition().x) + " Y: " + std::to_string(camera.getPosition().y) + " Z: " + std::to_string(camera.getPosition().z);
		glfwSetWindowTitle(window.getWindow(), title.c_str());
		
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderer.render(world, camera);

		window.swapBuffer();
		window.pollEvents();
	}

	window.shutdown();

	return 0;
}