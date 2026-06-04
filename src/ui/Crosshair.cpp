#include "Crosshair.h"


void Crosshair::setupQuad()
{
	float size = 0.03f;

	float vertices[] =
	{
	-size, -size, 0.0f, 0.0f,
	 size, -size, 1.0f, 0.0f,
	 size,  size, 1.0f, 1.0f,

	-size, -size, 0.0f, 0.0f,
	 size,  size, 1.0f, 1.0f,
	-size,  size, 0.0f, 1.0f
	};
}

Crosshair::Crosshair() : shader("shaders/ui.vert", "shaders/ui.frag")
{
	setupQuad();
	texture = loadTexture("textures/Crosshair.png");
}