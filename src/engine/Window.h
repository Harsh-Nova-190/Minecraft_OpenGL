#pragma once

#include "Core.h"

class Window
{
	public:

		GLFWwindow* window;
		int height;
		int width;

		Window(int width, int height, const char* title);

		bool initialize();
		bool shouldClose();
		void swapBuffer();
		void pollEvents();
		void shutdown();
		GLFWwindow* getWindow();
};