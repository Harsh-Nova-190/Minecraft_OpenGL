#include "BlockRenderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../engine/Core.h"

float vertices[] = {
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

BlockRenderer::BlockRenderer()
{
    initialize();
}

void BlockRenderer::initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	loadTextures();
}

unsigned int BlockRenderer::loadSingleTexture(const char* path)
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

void BlockRenderer::loadTextures()
{
	textures[(int)BlockType::Dirt] = loadSingleTexture("textures/Dirt.png");
	textures[(int)BlockType::Grass] = loadSingleTexture("textures/Grass.png");
	textures[(int)BlockType::Stone] = loadSingleTexture("textures/Stone.png");
	grassTopTexture = loadSingleTexture("textures/Grass_Top.png");
}

void BlockRenderer::drawBlock(Shader& shader, glm::vec3 position, FaceFlags faces, BlockType type)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, textures[(int)type]);
	glBindVertexArray(VAO);

	if(faces.front)
		glDrawArrays(GL_TRIANGLES, 0, 6);
	if(faces.back)
		glDrawArrays(GL_TRIANGLES, 6, 6);
	if (faces.left)   
		glDrawArrays(GL_TRIANGLES, 12, 6);
	if (faces.right)  
		glDrawArrays(GL_TRIANGLES, 18, 6);
	if (faces.top)
	{
		unsigned int topTexture = (type == BlockType::Grass) ? grassTopTexture : textures[(int)type];
		glBindTexture(GL_TEXTURE_2D, topTexture);
		glDrawArrays(GL_TRIANGLES, 24, 6);
	}
	if (faces.bottom)
	{
		unsigned int bottomTexture = (type == BlockType::Grass) ? textures[(int)BlockType::Dirt] : textures[(int)type];
		glBindTexture(GL_TEXTURE_2D, bottomTexture);
		glDrawArrays(GL_TRIANGLES, 30, 6);
	}
		
}
