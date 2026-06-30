#include "engine/Core.h"
#include "graphics/Shader.h"
#include "camera/Camera.h"
#include "world/helper/Block.h"
#include "engine/Window.h"
#include "world/World.h"
#include "renderer/WorldRenderer.h"
#include "ui/Crosshair.h"

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
	Window window(1280, 720, "Nova Voxel Engine");

	if(!window.initialize())
	{
		return -1;
	}

	WorldRenderer renderer;
	World world;
	Crosshair crosshair;

	//std::cout << world.chunkManager.getChunks().size() << std::endl;
	//std::cout << "Total number of Blocks: " << world.chunkManager.getChunks().size() * Chunk::SIZE * Chunk::SIZE * Chunk::SIZE << std::endl;

	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!window.shouldClose())
	{
		renderer.renderedBlockCount = 0;
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// camera movement
		camera.processKeyboardInput(window.getWindow(), deltaTime);

		world.chunkManager.update(camera.getPosition());

		// remove this after testing
		static float fpsTimer = 0.0f;
		static int fpsDisplay = 0;
		static int frameCount = 0;

		frameCount++;
		fpsTimer += deltaTime;

		if (fpsTimer >= 0.5f)  // update every half second
		{
			fpsDisplay = (int)(frameCount / fpsTimer);
			frameCount = 0;
			fpsTimer = 0.0f;
		}
		
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderer.render(world, camera);
		crosshair.draw();

		window.swapBuffer();
		window.pollEvents();

		std::string title = "Nova Voxel Engine | FPS: " + std::to_string(fpsDisplay) + " | X: " + std::to_string(camera.getPosition().x) + " Y: " + std::to_string(camera.getPosition().y) + " Z: " + std::to_string(camera.getPosition().z) + " | Rendered Blocks Times: " + std::to_string(renderer.renderedBlockCount);
		glfwSetWindowTitle(window.getWindow(), title.c_str());
	}

	window.shutdown();

	return 0;
}