#include "Crosshair.h"

#include <stb_image.h>

float CrosshairSize = 0.05f;

float CrosshairVertices[] =
{
-CrosshairSize, -CrosshairSize, 0.0f, 0.0f,
 CrosshairSize, -CrosshairSize, 1.0f, 0.0f,
 CrosshairSize,  CrosshairSize, 1.0f, 1.0f,

-CrosshairSize, -CrosshairSize, 0.0f, 0.0f,
 CrosshairSize,  CrosshairSize, 1.0f, 1.0f,
-CrosshairSize,  CrosshairSize, 0.0f, 1.0f
};


Crosshair::Crosshair() : shader("shaders/ui.vert", "shaders/ui.frag")
{
	initialize();
}

void Crosshair::initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CrosshairVertices), CrosshairVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	texture = loadTexture("textures/crosshair.png");
}

unsigned int Crosshair::loadTexture(const char* path)
{
	unsigned int Tex;
	glGenTextures(1, &Tex);
	glBindTexture(GL_TEXTURE_2D, Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Texture Failed to Load: " << path << std::endl;
	}
	stbi_image_free(data);
	return Tex;
}

void Crosshair::draw()
{
	glDisable(GL_DEPTH_TEST);
	shader.use();
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glEnable(GL_DEPTH_TEST);
}