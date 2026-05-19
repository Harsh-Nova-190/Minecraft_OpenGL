#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../graphics/Shader.h"

class Block
{
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texture;

	Block();
	void draw(Shader& shader, glm::vec3 position);

private:

	void setupMesh();
	void loadTexture();

};