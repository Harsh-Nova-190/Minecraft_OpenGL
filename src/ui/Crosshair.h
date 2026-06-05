#pragma once
#include "../graphics/Shader.h"

class Crosshair
{
public:
	Crosshair();
	void initialize();
	void draw();
	void verticalDraw();

private:
	unsigned int VAO, VBO, texture;

	Shader shader;

	unsigned int  loadTexture(const char* path);
};