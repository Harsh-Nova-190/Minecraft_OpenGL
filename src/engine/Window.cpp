#include "Window.h"
#include "Core.h"


Window::Window(int width, int height, const char* title)
{
	std::cout << "Path of the Game: " << std::filesystem::current_path() << std::endl;

	this->height = height;
	this->width = width;
	
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

bool Window::initialize()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n" << std::endl;
		return false;
	}
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Minecraft Clone", nullptr, nullptr);

	if (!window)
	{
		std::cout << "Failed to create GLFW window\n" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n" << std::endl;
		return false;
	}

	glViewport(0, 0, width, height);

	return true;
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffer()
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::shutdown()
{
	glfwTerminate();
}
GLFWwindow* Window::getWindow()
{
	return window;
}