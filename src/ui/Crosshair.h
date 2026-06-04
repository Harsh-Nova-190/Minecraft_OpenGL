#pragma once
#include "../graphics/Shader.h"

class Crosshair
{
public:
	Crosshair();

	void draw();

private:
	unsigned int VAO, VBO, texture;

	Shader shader;

	void setupQuad();
	unsigned int  loadTexture(const char* path);
};